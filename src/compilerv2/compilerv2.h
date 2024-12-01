/**
 * The compiler of Quickfall.
 */

#ifndef COMPILER_2_H
#define COMPILER_2_H

#include "../parser/ast.h"
#include "./objects.h"

enum Platform {
	ATT_WINDOWS,
	ATT_LINUX
};

/**
 * A context is the less abstract way Quickfall represents the code before converting it to assembly.
 */
struct Context {
	struct Variable* variables;
	struct Function* functions;
	int variableCount;
	int functionCount;
};

/**
 * Parses the AST tree into a context.
 */
struct Context parseContext(struct ASTNode* node);

char* compileV2(struct Context context);

#endif
