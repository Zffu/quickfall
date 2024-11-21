/**
 * Compiling for Windows x86-64 systems.
 */

#include "../../parser/ast.h"
#include "../compiler.h"

struct CompilerOutput win64compile(struct ASTNode* node);

/**
 * Gets the Assembly output of the AST node.
 */
char* win64output(struct ASTNode* node);