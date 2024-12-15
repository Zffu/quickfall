/**
 * The compiler's internal IR.
 */

#include "../utils/hashmap.h"

#ifndef IR_H
#define IR_H

enum IRNodeType {
	IR_FUNCTION,

	IR_VARIABLE,
	IR_FUNCTION_ARGUMENT,
	IR_FUNCTION_BODY_VARIABLE
};

typedef enum IRNodeType IR_TYPE;

struct IRNode {

	IR_TYPE nodeType;

	// Shared Properties
	
	char* nodeName;
	char* type;

	// Variable Properties
	char* value;

	// Function Properties
	struct IRNode* variables;
	int variableIndex;

	struct Hashmap variableMap;

	AST_NODE* tree;
};

typedef struct IRNode IR_NODE;

struct IRContext {
	IR_NODE* nodes;
	int nodeIndex;

	struct Hashmap nodeMap;
};

typedef struct IRContext IR_CTX;

#endif
