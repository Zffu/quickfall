/**
 * The compiler of Quickfall.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./compilerv2.h"
#include "./objects.h"
#include "../parser/ast.h"
#include "../utils/logging.h"

struct Context parseContext(struct ASTNode* node) {
	struct Context ctx = {0};
	
	ctx.variables = malloc(sizeof(struct Variable) * 50);
	ctx.functions = malloc(sizeof(struct Function) * 50);

	ctx.variableCount = 0;
	ctx.functionCount = 0;

	while(node->next != NULL) {
		node = node->next;
		switch (node->type) {
			case AST_VARIABLE_DEF:
				ctx.variables[ctx.variableCount].name = node->left->value;
				ctx.variables[ctx.variableCount].type = "none";
				
				if(node->right->type == AST_VARIABLE_VALUE) {
					ctx.variables[ctx.variableCount].value = node->right->value;
				}
				else if(node->right->type == AST_VARIABLE) {
					if(node->right->value == ctx.variables[ctx.variableCount].name) {
						printf("%sError: Cannot assign a variable's value to itself!\n", TEXT_HRED);
						return NULL;
					}

					//todo: change this to an hashmap before pr finished.
					
					for(int i = 0; i < ctx.variableCount; ++i) {
						if(strcmp(ctx.variables[i].name, node->right->value) == 0) {
							ctx.variables[ctx.variableCount].value = ctx.variables[i].value;
							break;
						}
					}
				}
				else {
					printf("%sError: Dissallowed token type as a variable value!\n", TEXT_HRED);
					return NULL;
				}

				ctx.variableCount++;
				break;	
			case AST_FUNCTION_DEF:
				ctx.functions[ctx.functionCount].name = node->left->left->value;
				while(node->left->right->next != NULL) {
					node->left->right = node->left->right->next;

					int c = ctx.functions[ctx.functionCount].variableCount;

					ctx.functions[ctx.functionCount].variables[c].name = node->left->right->right->value;
					ctx.functions[ctx.functionCount].variables[c].type = node->left->right->left->value;
					ctx.functions[ctx.functionCount].variableCount++;
				}

				ctx.functions[ctx.functionCount].body = node->right;
				ctx.functionCount++;
				break;
		}
	}

}

