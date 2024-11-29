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

<<<<<<< HEAD
=======
struct FunctionBody {
	struct Variable* vars;
    int varCount;
};

>>>>>>> b8de72a8cfe867e47214f59c63d4bebb1b977cd0
struct Function {
	char* name;
	struct Variable* variables;
	int variableCount;
	struct ASTNode* body;
};



#endif
