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
    enum Platform p = platformFromString(platform);

    char start[1024] = {""};
    char sections[1024] = {""};
    char startOutput[1024] = {"main:"};

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
                if(p == WINDOWS) {
                    strcat(start, "\n\nsection .text");
                    globalDef(start, node->right->next->value);
                    strcat(start, "\n\n");
                }
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
            else if(p == WINDOWS) {
                if(strcmp(node->left->value, "extrnLoad") == 0) {
                    extrnLoad(start, node->right->next->value);
                }
                else if(strcmp(node->left->value, "push") == 0) {
                    push(startOutput, node->right->next->value);
                }
                else if(strcmp(node->left->value, "call") == 0) {
                    call(startOutput, node->right->next->value);
                }
                else if(strcmp(node->left->value, "add") == 0) {
                    add(startOutput, node->right->next->value, node->right->next->next->value);
                }
                else if(strcmp(node->left->value, "ret") == 0) {
                    ret(startOutput);
                }
            }

        }
    }

    struct CompilerOutput o;
    strcat(o.output, start);

    if(p != WINDOWS) {
        strcat(o.output, sections);
        strcat(o.output, startOutput);
    }
    else {
        strcat(o.output, startOutput);
        strcat(o.output, sections);
    }

    printf("\n%s", o.output);
    return o;
}