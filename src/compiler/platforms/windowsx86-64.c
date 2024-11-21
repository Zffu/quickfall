/**
 * Compiling for Windows x86-64 systems.
 */

#include <string.h>
#include <stdio.h>

#include "../../parser/ast.h"
#include "../compiler.h"

/**
 * Gets the assembly output of the AST Node.
 */
void win64(struct CompilingContext ctx, struct ASTNode* node) {
    if(node->type == AST_FUNCTION_CALL) {
        // Handles the low level function here for now.
        
        if(strcmp(node->left->value, "salloc") == 0) {
            strcat(ctx.main, "\n    subq    $");
            strcat(ctx.main, node->right->next->value);
            strcat(ctx.main, ", %rsp");
        }
        else if(strcmp(node->left->value, "sfree") == 0) {
            strcat(ctx.main, "\n    addq    $");
            strcat(ctx.main, node->right->next->value);
            strcat(ctx.main, ", %rsp");
        }
        else if(strcmp(node->left->value, "stackPut") == 0) {
            strcat(ctx.defaultSection, "\n    .");
            strcat(ctx.defaultSection, node->right->next->value);
            strcat(ctx.defaultSection, " \"");
            strcat(ctx.defaultSection, node->right->next->next->value);
            strcat(ctx.defaultSection, "\"");
        }
        else if(strcmp(node->left->value, "call") == 0) {
            strcat(ctx.main, "\n    call    ");
            strcat(ctx.main, node->right->next->value);
        }
        else if(strcmp(node->left->value, "mov") == 0) {
            strcat(ctx.main, "\n    leaq    .");
            strcat(ctx.main, node->right->next->value);
            strcat(ctx.main, "(%");
            strcat(ctx.main, node->right->next->next->value);
            strcat(ctx.main, "), %");
            strcat(ctx.main, node->right->next->next->next->value);
        }
        else {
            // If the function isn't an internal, jump to it.
            strcat(ctx.main, "\n    jmp .");
            strcat(ctx.main, node->left->value);
        }
    }
    else if(node->type == AST_FUNCTION_DEF) {
        strcat(ctx.sections, "\n.");
        strcat(ctx.sections, node->left->value);
        strcat(ctx.sections, ":");

        win64(ctx, node->right); // Parses the AST_GENERIC Node.
    }
    else if(node->type == AST_GENERIC) {
        struct ASTNode* n = node;
        while (n->next != NULL) {
            n = n->next;

            win64(ctx, n);
        }
    }
    else {
        printf("Error: AST Node of type %d could not be converted to x64 assembly!\n", node->type);
    }
}