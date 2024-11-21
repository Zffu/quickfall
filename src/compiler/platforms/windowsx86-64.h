/**
 * Compiling for Windows x86-64 systems.
 */

#include "../../parser/ast.h"
#include "../compiler.h"

/**
 * Gets the Assembly output of the AST node.
 */
void win64output(struct CompilingContext ctx, struct ASTNode* node);