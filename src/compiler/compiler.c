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

	ctx->nodeIndex = 0;
	ctx->nodeHashmap = createHashmap(512,200);
}

/**
 * Compiles the Context tree to an executable named the provided file name.
 * @param ctx the IR context.
 * @param char the output file name.
 */
void compile(IR_CTX* ctx, char* outputFileName) {

}
