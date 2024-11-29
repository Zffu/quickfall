/**
 * Compiling objects such as functions, variables...
 */

#ifndef COMPILER_OBJECTS_H
#define COMPILER_OBJECTS_H

#include "../parser/ast.h"

struct Variable {
	char* name;
	char* value;
	char* type;
	byte type; // 0 = variable, 1 = Func argument, 2 = Function body argument
};

struct Function {
	char* name;
	struct Variable* variables;
	int variableCount;
	struct ASTNode* body;
};

#endif
