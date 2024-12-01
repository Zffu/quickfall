/**
 * The compiler of Quickfall.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./compilerv2.h"
#include "./objects.h"
#include "../parser/ast.h"
#include "../utils/logging.c"

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
				ctx.variables[ctx.variableCount].type = node->right->value;
				
				if(node->right->type == AST_VARIABLE_VALUE) {
					ctx.variables[ctx.variableCount].value = node->right->value;
				}
				else {
					printf("%sError: Invalid token type as a variable value!\n", TEXT_HRED);
					return ctx;
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

