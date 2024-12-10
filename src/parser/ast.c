/**
 * The AST Nodes in Quickfall.
 */

#include <stdlib.h>

#include "./ast.h"

/**
 * Creates a new AST Node.
 * @param type the AST type of the node.
 */
AST_NODE* createASTNode(enum ASTNodeType type) {
	AST_NODE* node = malloc(sizeof(AST_NODE));

	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;

	return node;
}
