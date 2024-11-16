#include <stdlib.h>
#include "./ast.h"

/**
 * Creates an AST node.
 */
struct ASTNode* createASTNode(enum ASTNodeType type, char* value) {
    struct ASTNode* node = malloc(sizeof(struct ASTNode));
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->value = value;
    node->type = type;
    node->end = 0;

    return node;
}
