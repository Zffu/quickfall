/**
 * The compiler of Quickfall.
 */

#include "./compiler.h"
#include "./ir.h"

#include "../parser/ast.h"

/**
 * Parses the AST tree into a context.
 * @param tree the AST tree.
 */
IR_CTX* makeContext(AST_NODE* tree) {
	
}

/**
 * Compiles the Context tree to an executable named the provided file name.
 * @param ctx the IR context.
 * @param char the output file name.
 */
void compile(IR_CTX* ctx, char* outputFileName) {

}
