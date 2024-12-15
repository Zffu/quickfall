/**
 * The compiler of Quickfall.
 */

#include <stdlib.h>

#include "./compiler.h"
#include "./ir.h"

#include "../parser/ast.h"

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

	while(tree->next != NULL) {
		tree = tree->next;

		switch(tree->type) {
			case AST_VARIABLE_DECLARATION:

				

				if(ctx->nodeIndex > buffSize) {
					buffSize = buffSize * 1.5;
					ctx->nodes = realloc(ctx->nodes, buffSize);
				}
		}
	}
}

/**
 * Compiles the Context tree to an executable named the provided file name.
 * @param ctx the IR context.
 * @param char the output file name.
 */
void compile(IR_CTX* ctx, char* outputFileName) {

}
