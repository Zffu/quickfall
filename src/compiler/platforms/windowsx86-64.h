/**
 * Compiling for Windows x86-64 systems.
 */

#include "../../parser/ast.h"
#include "../compiler.h"

/**
 * Gets the Assembly output of the AST node.
 */
char* win64output(struct ASTNode* node);