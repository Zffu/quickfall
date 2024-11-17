/**
 * Compiling for Windows x86-64 systems.
 */

#include <string.h>
#include "../../parser/ast.h"
#include "../compiler.h"

struct CompilerOutput win64compile(struct ASTNode* node) {
    char segments[1024] = {".LC0\n    .globl main\n"};
    char main[1024] = {"main:"};

    while(node->next != NULL) {
        node = node->next;

        if(node->type == AST_FUNCTION_CALL) {
            if(strcmp(node->left->value, "salloc") == 0) {
                strcat(main, "\n    subq    $");
                strcat(main, node->right->next->value);
                strcat(main, ", %rsp");
            }
            else if(strcmp(node->left->value, "sfree") == 0) {
                strcat(main, "\n    addq    $");
                strcat(main, node->right->next->value);
                strcat(main, ", %rsp");
            }
            else if(strcmp(node->left->value, "stackPut") == 0) {
                strcat(segments, "\n    .");
                strcat(segments, node->right->next->value);
                strcat(segments, " '");
                strcat(segments, node->right->next->next->value);
                strcat(segments, "'");
            }
            else if(strcmp(node->left->value, "call") == 0) {
                strcat(main, "\n    call    ");
                strcat(main, node->right->next->value);
            }
            else if(strcmp(node->left->value, "mov") == 0) {
                strcat(main, "\n    leaq    .");
                strcat(main, node->right->next->value);
                strcat(main, "(%");
                strcat(main, node->right->next->next->value);
                strcat(main, "), %");
                strcat(main, node->right->next->next->next->value);
            }
        }
    }  

    strcat(main, "\n    ret");  

    struct CompilerOutput o;

    strcat(o.output, segments);
    strcat(o.output, "\n\n");
    strcat(o.output, main);
    strcat(o.output, "\n");

    return o;
}