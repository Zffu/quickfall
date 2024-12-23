/**
 * The header file of AST nodes in Quickfall.
 */

#ifndef AST_2_H
#define AST_2_H

/**
 * The type of AST Node(s).
 */
enum ASTNodeType {

	AST_ROOT, // A root of an AST tree, can either represent the first node of the tree or a function body.

	AST_TYPE, // Represents a datatype precision in an AST Node.
	AST_VARIABLE_NAME, // Represents a variable / parameter name precision in an AST Node.
	AST_VARIABLE_VALUE,

	AST_VARIABLE_DECLARATION,
	AST_VARIABLE_REFERENCE,

	AST_ASM_FUNCTION_DECLARATION,

	AST_FUNCTION_DECLARATION,
	AST_FUNCTION_HEADER,

	AST_FUNCTION_INVOKE,

	AST_FUNCTION_ROOT,

	AST_MATH_OPERATOR,
	AST_MATH_OPERATION,
	AST_MATH_OP_HEADER,

	AST_PARAMETER // A function parameter AST Node, used in function declaration.
};

/**
 * An AST Node. Has a tree-ish structure.
 */
struct ASTNode {

	struct ASTNode* left;
	struct ASTNode* right;
	struct ASTNode* next;

	enum ASTNodeType type;
	char* value;
	int endingIndex; // The index which the parsing ended

};

typedef struct ASTNode AST_NODE;

/**
 * Creates a new AST Node.
 * @param type the AST type of the node.
 */
AST_NODE* createASTNode(enum ASTNodeType type);

#endif
