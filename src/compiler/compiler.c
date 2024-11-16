/**
 * The compiler of Quickfall.
 */

#include <string.h>
#include <stdio.h>
#include "../parser/ast.h"

void compile(struct ASTNode* node) {

    char output[1024] = {"_start:"};


    while(node->next != NULL) {
        node = node->next;

        if(node->type == AST_FUNCTION_CALL) {
            if(strcmp(node->left->value, "moveRegistry") == 0) {
                char instruction[32] = {"\n    mov "};
                strcat(instruction, node->right->next->value);
                strcat(instruction, ", ");
                strcat(instruction, node->right->next->next->value);
                strcat(output, instruction);
            }
            else if(strcmp(node->left->value, "systemCall") == 0) {
                char instruction[32] = {"\n    syscall"};
                strcat(output, instruction);
            }
        }
    }

    printf("\n%s", output);
}