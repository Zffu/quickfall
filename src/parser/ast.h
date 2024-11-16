#ifndef AST_H
#define AST_H

/**
 * The type of AST nodes
 */
enum ASTNodeType {
    AST_VARIABLE_DEF,
    AST_FUNCTION_DEF,
    AST_FUNCTION_CALL,
    AST_VARIABLE,
    AST_PARAMETERS,
    AST_PARAM,
    AST_PARAM_TYPE,
    AST_PARAM_NAME
};

/**
 * An AST node.
 */
struct ASTNode {
    enum ASTNodeType type;
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* next;
    int end;
};

/**
 * Creates an AST node.
 */
struct ASTNode* createASTNode(enum ASTNodeType type);

#endif