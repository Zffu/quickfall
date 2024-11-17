/**
 * The compiler of Quickfall.
 */

#include <string.h>
#include <stdio.h>
#include "../parser/ast.h"

#include "./platforms/linux.h"
#include "./platforms/windows.h"

enum Platform {
    WINDOWS,
    LINUX
};

enum Platform platformFromString(char* platform) {
    if(strcmp(platform, "win")) return WINDOWS;
    else LINUX;
}

struct CompilerOutput {
    char output[2048];
};

struct CompilerOutput compile(struct ASTNode* node, char* platform) {
    enum Platform p = LINUX;

    char sections[1024] = {""};
    char startOutput[1024] = {"_start:"};

    while(node->next != NULL) {
        node = node->next;

        if(node->type == AST_FUNCTION_CALL) {
            
            printf("%s\n", node->left->value);

            if(strcmp(node->left->value, "secDec") == 0) {
                strcat(sections, "section .");
                strcat(sections, node->right->next->value);
                continue;
            }
            else if(strcmp(node->left->value, "secEnd") == 0) {
                strcat(sections, "\n\n");
            }
            else if(strcmp(node->left->value, "gDef") == 0) {
                if(p == WINDOWS) globalDef(sections, node->right->next->value);
                else {
                    strcat(sections, "section .text");
                    sectG(sections, node->right->next->value);
                    strcat(sections, "\n\n");
                }
            }
            else if(strcmp(node->left->value, "decSec") == 0) {
                if(p == WINDOWS) winDecSec(sections,node->right->next->value, node->right->next->next->value, node->right->next->next->next->value);
                else decSec(sections, node->right->next->value, node->right->next->next->value, node->right->next->next->next->value);
            }
            else if(p == LINUX) {
                if(strcmp(node->left->value, "movR") == 0) {
                    movR(startOutput, node->right->next->value, node->right->next->next->value);
                }
                else if(strcmp(node->left->value, "syscall") == 0) {
                    syscall(startOutput);
                }
                else if(strcmp(node->left->value, "regXOR") == 0) {
                    regXOR(startOutput, node->right->next->value, node->right->next->next->value);
                }
            }

        }
    }

    struct CompilerOutput o;
    strcat(o.output, sections);
    strcat(o.output, startOutput);

    printf("\n%s", o.output);
    return o;
}