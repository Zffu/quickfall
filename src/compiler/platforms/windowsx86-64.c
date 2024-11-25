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
            // If the function isn't an internal, jump to it!
	    if(node->right->next != NULL) { 
            	int argCount = 0;
            	while(node->right->next != NULL) {
			node->right = node->right->next;

                	char b[5] = {""};
                	sprintf(b, "%d", ctx.section++ + 1);

                	strcat(ctx.sections, "\n.");
                	strcat(ctx.sections, "LC");
                	strcat(ctx.sections, b);
                	strcat(ctx.sections, ":");
                	strcat(ctx.sections, "\n    .ascii \"");
                	strcat(ctx.sections, node->right->value);
                	strcat(ctx.sections, "\\0\"");

                	strcat(funcBuff, "\n    leaq    .LC");

                	strcat(funcBuff, b);
                	strcat(funcBuff, "(%rip), %rax");
                	strcat(funcBuff, "\n    movq %rax,");

                	switch(argCount) {
                    		case 0:
                        		strcat(funcBuff, "%rcx");
                        		break;
                    		case 1:
                        		strcat(funcBuff, "%rdx");
                        		break;
                    		case 2:
                        		strcat(funcBuff, "%r8");
                        		break;
                    		case 3:
                        		strcat(funcBuff, "%r9");
                        		break;            
                	}

                	argCount++;
            	}
	    }

            strcat(funcBuff, "\n    jmp .");
            strcat(funcBuff, node->left->value);
        }
    }
    else if(node->type == AST_FUNCTION_DEF) {
        strcat(ctx.sections, "\n.");
        strcat(ctx.sections, node->left->left->value);
        strcat(ctx.sections, ":");

        win64(ctx, node->right, genericState); // Parses the AST_GENERIC Node.
        strcat(ctx.sections, "\n    ret\n");
    }
    else if(node->type == AST_FUNCTION_GENERIC || node->type == AST_GENERIC) {
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
