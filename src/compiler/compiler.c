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

#include "./pe/pe.h"

/**
 * Compiles the Context tree to an executable named the provided file name.
 * @param ctx the IR context.
 * @param out the output file.
 */
void compile(FILE* out) {
}
