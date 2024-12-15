/**
 * The compiler's internal IR.
 */

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

}

typedef IR_NODE struct IRNode;

#endif
