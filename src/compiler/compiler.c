/**
 * The compiler of Quickfall.
 */

#include <string.h>
#include <stdio.h>
#include "../parser/ast.h"

void compile(struct ASTNode* node) {
    char sections[1024];
    char startOutput[1024] = {"_start:"};


    while(node->next != NULL) {
        node = node->next;

        if(node->type == AST_FUNCTION_CALL) {
            if(strcmp(node->left->value, "moveRegistry") == 0) {
                char instruction[32] = {"\n    mov "};
                strcat(instruction, node->right->next->value);
                strcat(instruction, ", ");
                strcat(instruction, node->right->next->next->value);
                strcat(startOutput, instruction);
            }
            else if(strcmp(node->left->value, "systemCall") == 0) {
                char instruction[32] = {"\n    syscall"};
                strcat(startOutput, instruction);
            }
            else if(strcmp(node->left->value, "declareSect") == 0) {
                char instruction[32] = {"section ."};
                strcat(instruction, node->right->next->value);
                strcat(sections, instruction);
            }
            else if(strcmp(node->left->value, "sectDeclare") == 0) {
                char instruction[32] = {"\n    "};
                strcat(instruction, node->right->next->value);
                strcat(instruction, " ");
                strcat(instruction, node->right->next->next->value);
                strcat(instruction, " '");
                strcat(instruction, node->right->next->next->next->value);
                strcat(instruction, "', 0");
                strcat(sections, instruction);
            }
            else if(strcmp(node->left->value, "registryXOR") == 0) {
                strcat(startOutput, "\n    xor ");
                strcat(startOutput, node->right->next->value);
                strcat(startOutput, ", ");
                strcat(startOutput, node->right->next->next->value);
            }
            else if(strcmp(node->left->value, "sectVoid") == 0) {
                strcat(sections, "\n\n");
            }
            else if(strcmp(node->left->value, "sectGlobal") == 0) {
                strcat(sections,"\n    global ");
                strcat(sections, node->right->next->value);
            }
        }
    }

    char output[2048];
    strcat(output, sections);
    strcat(output, startOutput);

    printf("\n%s", output);
}