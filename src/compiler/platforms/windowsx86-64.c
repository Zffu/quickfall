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
void win64(struct CompilingContext ctx, struct ASTNode* node, int genericState) {
    if(node->type == AST_FUNCTION_CALL) {

        char* funcBuff = (genericState == 0 ? ctx.main : ctx.sections);

        // Handles the low level function here for now.
        
        if(strcmp(node->left->value, "salloc") == 0) {
            strcat(funcBuff, "\n    subq    $");
            strcat(funcBuff, node->right->next->value);
            strcat(funcBuff, ", %rsp");
        }
        else if(strcmp(node->left->value, "sfree") == 0) {
            strcat(funcBuff, "\n    addq    $");
            strcat(funcBuff, node->right->next->value);
            strcat(funcBuff, ", %rsp");
        }
        else if(strcmp(node->left->value, "stackPut") == 0) {
            strcat(ctx.defaultSection, "\n    .");
            strcat(ctx.defaultSection, node->right->next->value);
            strcat(ctx.defaultSection, " \"");
            strcat(ctx.defaultSection, node->right->next->next->value);
            strcat(ctx.defaultSection, "\"");
        }
        else if(strcmp(node->left->value, "call") == 0) {
            strcat(funcBuff, "\n    call    ");
            strcat(funcBuff, node->right->next->value);
        }
        else if(strcmp(node->left->value, "mov") == 0) {
            strcat(funcBuff, "\n    leaq    .");
            strcat(funcBuff, node->right->next->value);
            strcat(funcBuff, "(%");
            strcat(funcBuff, node->right->next->next->value);
            strcat(funcBuff, "), %");
            strcat(funcBuff, node->right->next->next->next->value);
        }
        else {
            // If the function isn't an internal, jump to it.
            strcat(funcBuff, "\n    jmp .");
            strcat(funcBuff, node->left->value);
        }
    }
    else if(node->type == AST_FUNCTION_DEF) {
        strcat(ctx.sections, "\n.");
        strcat(ctx.sections, node->left->value);
        strcat(ctx.sections, ":");

        win64(ctx, node->right, genericState); // Parses the AST_GENERIC Node.
    }
    else if(node->type == AST_GENERIC || node->type == AST_FUNCTION_GENERIC) {
        struct ASTNode* n = node;
        while (n->next != NULL) {
            n = n->next;

            win64(ctx, n, (node->type == AST_GENERIC ? 0 : 1));
        }
    }
    else {
        printf("Error: AST Node of type %d could not be converted to x64 assembly!\n", node->type);
    }
}