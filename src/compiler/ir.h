/**
 * The compiler's internal IR.
 */

#include "../parser/ast.h"

#include "../utils/hashmap.h"

#ifndef IR_H
#define IR_H

enum IRNodeType {
	IR_FUNCTION,

	IR_ASM_FUNCTION,

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
	void* value;
	int valueSize;

	// Function Properties
	struct IRNode** variables;
	int variableIndex;

	struct Hashmap* variableMap;

	AST_NODE* tree;
};

typedef struct IRNode IR_NODE;

struct IRContext {
	IR_NODE** nodes;
	int nodeIndex;

	struct Hashmap* nodeMap;

	IR_NODE* mainFunc;

};

typedef struct IRContext IR_CTX;

/**
 * Creates an IR node based on the type and the name given.
 * @param type the IR type of the node.
 * @param nodeName the name of the IR node.
 */
inline extern IR_NODE* createIRNode(IR_TYPE type, char* nodeName);

#endif
