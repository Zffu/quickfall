/**
 * The compiler of Quickfall.
 */

#include <string.h>
#include <stdio.h>
#include "../parser/ast.h"
#include "./platforms/linux.h"

struct CompilerOutput {
    char output[2048];
};

struct CompilerOutput compile(struct ASTNode* node) {
    char sections[1024] = {""};
    char startOutput[1024] = {"_start:"};

    while(node->next != NULL) {
        node = node->next;

        if(node->type == AST_FUNCTION_CALL) {
            if(strcmp(node->left->value, "secDec") == 0) {
                strcat(sections, "section .");
                strcat(sections, node->right->next->value);
                continue;
            }
            if(strcmp(node->left->value, "secEnd") == 0) {
                strcat(sections, "\n\n");
                continue;
            }
        }
    }

    struct CompilerOutput o;
    strcat(o.output, sections);
    strcat(o.output, startOutput);

    printf("\n%s", o.output);
    return o;
}