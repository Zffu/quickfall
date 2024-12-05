/**
 * The header file of AST nodes in Quickfall.
 */

#ifndef AST_2_H
#define AST_2_H

/**
 * The type of AST Node(s).
 */
enum ASTNodeType {

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

} AST_NODE;

#endif
