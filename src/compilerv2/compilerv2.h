/**
 * The compiler of Quickfall.
 */

#ifndef COMPILER_2_H
#define COMPILER_2_H

#include "../parser/ast.h"

/**
 * A context is the less abstract way Quickfall represents the code before converting it to assembly.
 */
struct Context {

};

/**
 * Parses the AST tree into a context.
 */
struct Context parseContext(struct ASTNode* node);

#endif
