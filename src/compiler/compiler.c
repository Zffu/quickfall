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

struct CompilerOutput compile(struct ASTNode* node, char* platform) {
    enum Platform p = platformFromString(platform);

    struct CompilerOutput o;

    while(node->next != NULL) {
        node = node->next;

        if(node->type == AST_USE_STDL) {

            printf("Importing %s from STDL!\n", node->right->value);

            char fileName[32] = "stdl/";

            //
            // todo: move stdl loading somewhere else
            //

            printf("ssdsd\n");
            strcat(fileName, node->right->value);
            strcat(fileName, ".qfall"); // Do not dynamically check the extension for now.

            printf("djskjokjdsjsd\n");

            FILE* fptr = fopen(fileName, "r");

            if(fptr == NULL) {
                printf("Error: Couldn't import %s from the standart library! Are you sure it is correct?\n");
                continue;
            }

            printf("vp\n");

            fseek(fptr, 0, SEEK_END);
            int size = ftell(fptr);
            fseek(fptr, 0, SEEK_SET);

            char* buff = (char*) malloc(size);
            fread(buff, 1, size, fptr);
            fclose(fptr);

            printf("wat\n");

            struct LexerResult result = runLexer(buff);
            struct ASTNode* n = runParser(result);

            printf("skibidi\n");
            while (n->next != NULL) {
                n = n->next;

                if(n->type == AST_FUNCTION_DEF) {
                    printf("Defined function %s\n", n->right->left->value);
                }
            }
        }
    }

    return o;
}