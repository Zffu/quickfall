/**
 * The compiler of Quickfall.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../parser/ast.h"
#include "../parser/parser.h"
#include "../lexer/lexer.h"

#include "./platforms/linux.h"
#include "./platforms/windowsx86-64.h"

enum Platform {
    WINDOWS,
    LINUX
};

enum Platform platformFromString(char* platform) {
    if(strcmp(platform, "win")) return WINDOWS;
    else LINUX;
}

char* compile(struct ASTNode* node, char* platform) {
    enum Platform p = platformFromString(platform);

    struct CompilingContext ctx;

    // Default size buffers for now, todo: use realloc for less memory usage.
    ctx.defaultSection = malloc(512);
    ctx.sections = malloc(1024);
    ctx.main = malloc(1024);

    while(node->next != NULL) {
        node = node->next;

        if(node->type == AST_USE_STDL) {

            printf("Importing %s from STDL!\n", node->right->value);

            char fileName[32] = "stdl/";

            //
            // todo: move stdl loading somewhere else
            //

            strcat(fileName, node->right->value);
            strcat(fileName, ".qfall"); // Do not dynamically check the extension for now.

            FILE* fptr = fopen(fileName, "r");

            if(fptr == NULL) {
                printf("Error: Couldn't import %s from the standart library! Are you sure it is correct?\n");
                continue;
            }


            fseek(fptr, 0, SEEK_END);
            int size = ftell(fptr);
            fseek(fptr, 0, SEEK_SET);

            char* buff = (char*) malloc(size);
            fread(buff, 1, size, fptr);
            fclose(fptr);

            struct LexerResult result = runLexer(buff);
            struct ASTNode* n = runParser(result);

            if(p == WINDOWS) win64(ctx, n);
        }
    }

    char* buff = malloc(2048);
    buff[0] = "\0";

    strcat(buff, ctx.defaultSection);
    strcat(buff, ctx.sections);
    strcat(buff, ctx.main);
    strcat(buff, "\n    ret\n");

    return buff;
}