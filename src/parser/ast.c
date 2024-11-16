#include <stdlib.h>
#include <string.h>
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
    node->end = 0;

    memset(node->value, 0, sizeof(node->value));

    return node;
}
