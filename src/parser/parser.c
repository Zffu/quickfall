/**
 * The parser of Quickfall.
 */

#include "../lexer/tokens.h"
#include "../lexer/lexer.h"
#include "./ast.h"
#include <stdio.h>
#include <string.h>

struct ASTNode* parseParameters(struct LexerResult result, int index);
struct ASTNode* parseFunctionDeclaration(struct LexerResult result, int index);
struct ASTNode* parseExpression(struct LexerResult result, int index, int end);


/**
 * Parses parameters of a function.
 */
struct ASTNode* parseParameters(struct LexerResult result, int index) {
    struct ASTNode* root = NULL;
    struct ASTNode* current = NULL;
    int mode = 0;

    for(; index < result.size + 1; ++index) {
        struct Token t = result.tokens[index];

        if(t.type == PAREN_CLOSE) {
            root->end = index;
            return root;
        }

        if(t.type == COMMA) {
            if(mode != 2) {
                printf("Error: Parameters were not passed correctly!\n");
                return NULL;
            }

            struct ASTNode* node = createASTNode(AST_PARAM);
            current->next = node;
            current = node;
        }

        if(!root) {
            root = createASTNode(AST_PARAM);
            current = root;
        }

        root->end = index;

        if(!current->left) {
            current->left = createASTNode(AST_PARAM_TYPE);
            memcpy(current->left->value, result.tokens[index].value, strlen(result.tokens[index].value));
            mode = 1;
        }
        else if(!current->right) {
            current->right = createASTNode(AST_PARAM_NAME);
            memcpy(current->right->value, result.tokens[index].value, strlen(result.tokens[index].value));
            mode = 2;
        }
    }

    printf("Error: The paren wasn't closed!\n");
    return root;
}

/**
 * Parses a function declaration.
 */
struct ASTNode* parseFunctionDeclaration(struct LexerResult result, int index) {
    struct ASTNode* node = createASTNode(AST_FUNCTION_DEF);

    if(result.tokens[index + 2].type != PAREN_OPEN) {
        printf("Error: Excepted a paren after function name!\n");
        return;
    }

    struct ASTNode* parameters = parseParameters(result, index + 3);

    node->left = createASTNode(AST_FUNCTION_TEMPLATE);
    node->left->left = createASTNode(AST_FUNCTION_NAME);
    memcpy(node->left->left->value, result.tokens[index + 1].value, strlen(result.tokens[index + 1].value));
    node->left->right = parameters;

    if(!parameters) {
        printf("Error: Argument parsing went wrong!\n");
        return NULL;
    }

    index = parameters->end + 1;

    if(result.tokens[index].type != BRACKETS_OPEN) {
        printf("Error: Excepted function body declaration got %d instead!\n", result.tokens[index - 1].type);
        printf("Dump:\n");
        for(;index < result.size +1; ++index) {
            printf("Index: %d, Type: %d\n", index, result.tokens[index].type);
        }
        return NULL;
    }

    index++;

    int start = index;

    for(;index < result.size + 1; ++index) {
        struct Token t = result.tokens[index];

        if(t.type == BRACKETS_CLOSE) {
            node->right = parseExpression(result, start, index); //todo: make a function to remove the need to loop to find the closing point
        }

        printf("Token in method body: %d\n", t.type);
    }

    node->end = index;
    return node;
}

/**
 * Parses an expression in the specified range.
 */
struct ASTNode* parseExpression(struct LexerResult result, int index, int end) {
    struct ASTNode* root = createASTNode(AST_GENERIC);
    struct ASTNode* current = root;

    for(; index < end; ++index) {
        struct Token t = result.tokens[index];
        struct Token next = result.tokens[index + 1];

        if(t.type == FUNCTION) {

            if(next.type == KEYWORD) {
                struct ASTNode* node = parseFunctionDeclaration(result, index);

                if(node != NULL) {
                    index = node->end;
                    current->next = node;
                    current = node;
                }
            }
        }
    }

    return root;
}

struct ASTNode* runParser(struct LexerResult result) {
    return parseExpression(result, 0, result.size);
}
