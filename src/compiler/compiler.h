/**
 * The compiler of Quickfall.
 */

#ifndef COMPILER_H
#define COMPILER_H

#include "../utils/hashmap.h"
#include "../parser/ast.h"

/**
 * Compiles the Context tree to an executable named the provided name.
 * @param ctx the IR context.
 * @param char the output file.
 */
void compile(FILE* outputFileName);

#endif
