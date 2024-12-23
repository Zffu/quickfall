/**
 * The compiler of Quickfall.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "./compiler.h"
#include "./ir.h"

#include "../parser/ast.h"

#include "../utils/hash.h"
#include "../utils/hashmap.h"

/**
 * Parses the AST tree into a context.
 * @param tree the AST tree.
 */
IR_CTX* makeContext(AST_NODE* tree) {
	IR_CTX* ctx = malloc(sizeof(IR_CTX));

	int buffSize = 32;
	ctx->nodes = malloc(sizeof(IR_NODE) * 32);

	ctx->nodeIndex = 0;
	ctx->nodeMap = createHashmap(512,200);

	while(tree != NULL) {
		switch(tree->type) {
			case AST_VARIABLE_DECLARATION:

				int hash = hashstr(tree->left->value);

				if(hashGet(ctx->nodeMap, hash) != NULL) {
					printf("Variable %s is already declared!\n", tree->left->value);
					return NULL;
				}

				IR_NODE* node = createIRNode(IR_VARIABLE, tree->left->value);

				node->type = tree->value;

				if(tree->right != NULL && tree->right->value) node->value = tree->right->value;

				ctx->nodes[ctx->nodeIndex] = node;
				ctx->nodeIndex++;

				hashPut(ctx->nodeMap, hash, node);

				if(ctx->nodeIndex > buffSize) {
					buffSize = buffSize * 1.5;
					ctx->nodes = realloc(ctx->nodes, buffSize);
				}

				break;

			case AST_FUNCTION_DECLARATION:
				
				hash = hashstr(tree->left->right->value);

				if(hashGet(ctx->nodeMap, hash) != NULL) {
					printf("Function %s was already declared!\n", tree->left->right->value);
					return NULL;
				}

				node = createIRNode(IR_FUNCTION, tree->left->right->value);
				
				node->type = tree->left->value;
				
				while(tree->left->left->next != NULL) {

					IR_NODE* var = createIRNode(IR_FUNCTION_ARGUMENT, tree->right->value);

					node->variables[node->variableIndex] = var;
					node->variableIndex++;

					hashPut(node->variableMap, hashstr(tree->right->value), var);

					tree->left->left = tree->left->left->next;
				}

				ctx->nodes[ctx->nodeIndex] = node;
				ctx->nodeIndex++;

				hashPut(ctx->nodeMap, hash, node);
				break;

			case AST_ASM_FUNCTION_DECLARATION:
				hash = hashstr(tree->left->right->value);

				if(hashGet(ctx->nodeMap, hash) != NULL) {
					printf("Assembly function %s is already defined!\n");
					return NULL;
				}

				node = createIRNode(IR_ASM_FUNCTION, tree->left->right->value);

				node->value = tree->value;

				while(tree->left->left->next != NULL) {

					IR_NODE* var = createIRNode(IR_FUNCTION_ARGUMENT, tree->left->left->right->value);

					node->variables[node->variableIndex] = var;
					node->variableIndex++;

					hashPut(node->variableMap, hashstr(tree->left->left->right->value), var);


					tree->left->left = tree->left->left->next;
				}

				ctx->nodes[ctx->nodeIndex] = node;
				ctx->nodeIndex++;

				hashPut(ctx->nodeMap, hash, node);

				break;

		}

		tree = tree->next;
	}

	return ctx;
}

/**
 * Compiles the Context tree to an executable named the provided file name.
 * @param ctx the IR context.
 * @param char the output file name.
 */
void compile(IR_CTX* ctx, FILE* out) {

	uint8_t* buff = malloc(sizeof(uint8_t) * 512);
	int i = 0;

	int h = hashstr("main");

	if(hashGet(ctx->nodeMap, h) == NULL) {
		printf("Error: the main function wasn't defined!\n");
		return;
	}

	IR_NODE* node = hashGet(ctx->nodeMap, h);

	if(node->nodeType != IR_FUNCTION) {
		printf("Error: main must be a function!\n");
		return;
	}

	while(node->tree->next != NULL) {

		if(node->tree->type == AST_FUNCTION_INVOKE) {
			int hash = hashstr(node->tree->value);

			AST_NODE* wa = hashGet(ctx->nodeMap, hash);

			if(wa == NULL) {
				printf("Error: The %s function doesn't exist!\n", node->tree->value);
				return;
			}

			if(wa->type == IR_ASM_FUNCTION) {
				printf("%d", wa->value);
			}
		}

		node->tree = node->tree->next;
	}



}
