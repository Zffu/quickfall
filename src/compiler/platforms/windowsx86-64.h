/**
 * Compiling for Windows x86-64 systems.
 */

#include "../../parser/ast.h"
#include "../compiler.h"

#define WIN_64_DEFAULT_SECTION ".LC0:\n    .globl main"

/**
 * Gets the Assembly output of the AST node.
 */
void win64(struct CompilingContext ctx, struct ASTNode* node, int genericState);