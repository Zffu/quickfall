#include <stdlib.h>
#include "./ast.h"

/**
 * Creates an AST node.
 */
struct ASTNode* createASTNode(enum ASTNodeType type) {
    struct ASTNode* node = malloc(sizeof(struct ASTNode));
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->type = type;
    node->size = 0;

    return node;
}