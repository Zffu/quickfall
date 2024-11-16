/**
 * The parser of Quickfall.
 */

#include "../lexer/lexer.h"
#include "./ast.h"
#include <stdio.h>

/**
 * Parses parameters of a function.
 */
struct ASTNode* parseParameters(struct LexerResult result, int index) {
    struct ASTNode* root = NULL;
    struct ASTNode* current = NULL;

    for(; index < result.size + 1; ++index) {
        struct Token t = result.tokens[index];

        if(t.type == PAREN_CLOSE) {
            return root;
        }
        if(t.type != KEYWORD) {
            printf("Error: Arguments must be represented as litterals (got %d)\n", t.type);
            return NULL;
        }

        struct ASTNode* param = createASTNode(AST_PARAM);
        param->left = createASTNode(AST_PARAM_TYPE);
        param->right = createASTNode(AST_PARAM_NAME);

        if(!root) {
            root = param;
            current = param;
        }
        else {
            current->next = param;
            current = param;
        }

        current->size++;

        printf("Token in parameters: %d\n", t.type);
    }

    printf("Error: The paren wasn't closed!\n");
    return root;
}

/**
 * Parses a function declaration.
 */
void parseFunctionDeclaration(struct LexerResult result, int index) {
    if(result.tokens[index + 2].type != PAREN_OPEN) {
        printf("Error: Excepted a paren after function name!\n");
        return;
    }

    struct ASTNode* parameters = parseParameters(result, index + 3);

    if(!parameters) {
        printf("Error: Argument parsing went wrong!\n");
        return;
    }

    index += parameters->size + 6;

    if(result.tokens[index - 1].type != BRACKETS_OPEN) {
        printf("Error: Excepted function body declaration!\n");
        return;
    }

    for(;index < result.size; ++index) {
        struct Token t = result.tokens[index];

        if(t.type == BRACKETS_CLOSE) break;

        printf("Token in method body: %d\n", t.type);
    }
}

void runParser(struct LexerResult result) {
    for(int i = 0; i < result.size; ++i) {
        struct Token t = result.tokens[i];
        struct Token next = result.tokens[i + 1];

        if(t.type == FUNCTION) {

            if(next.type == KEYWORD) {
                parseFunctionDeclaration(result, i);
            }
        }
    }
}
