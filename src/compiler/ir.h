/**
 * The compiler's internal IR.
 */

#include "../../utils/hashmap.h"

#ifndef IR_H
#define IR_H

enum IRNodeType {
	IR_FUNCTION,

	IR_VARIABLE,
	IR_FUNCTION_ARGUMENT,
	IR_FUNCTION_BODY_VARIABLE
};

typedef IR_TYPE enum IRNodeType;

struct IRNode {

	IR_TYPE type;

	// Shared Properties
	
	char* nodeName;
	char* type;

	// Variable Properties
	char* value;

	// Function Properties
	IR_NODE* variables;
	int variableIndex;

	struct Hashmap variableMap;

}

typedef IR_NODE struct IRNode;

struct IRContext {
	IR_NODE* nodes;
	int nodeIndex;

	struct Hashmap nodeMap;
};

typedef IR_CTX struct IRContext;

#endif
