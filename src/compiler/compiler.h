/**
 * The compiler of Quickfall.
 */

#ifndef COMPILER_H
#define COMPILER_H

#include "../utils/hashmap.h"
#include "../parser/ast.h"

#include "./ir.h"

/**
 * Parses the AST tree into a context.
 * @param tree the AST tree.
 */
IR_CTX* makeContext(AST_NODE* tree);

/**
 * Compiles the Context tree to an executable named the provided name.
 * @param ctx the IR context.
 * @param char the output file name.
 */
void compile(IR_CTX* ctx, char* outputFileName);

#endif
