/**
 * The header file of AST nodes in Quickfall.
 */

#ifndef AST_2_H
#define AST_2_H

/**
 * The type of AST Node(s).
 */
enum ASTNodeType {
	AST_TYPE, // Represents a datatype precision in an AST Node.
	AST_VARIABLE_NAME, // Represents a variable / parameter name precision in an AST Node.
	AST_VARIABLE_VALUE,

	AST_VARIABLE_REFERENCE,

	AST_PARAMETER // A function parameter AST Node, used in function declaration.
}

/**
 * An AST Node. Has a tree-ish structure.
 */
typedef struct ASTNode {

	AST_NODE* left;
	AST_NODE* right;
	AST_NODE* next;

	enum ASTNodeType type;
	char* value;
	int endingIndex; // The index which the parsing ended

} AST_NODE;

/**
 * Creates a new AST Node.
 * @param type the AST type of the node.
 */
AST_NODE* createASTNode(enum ASTNodeType type);

#endif
