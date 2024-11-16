/**
 * The parser of Quickfall.
 */

#include "../lexer/tokens.h"
#include "../lexer/lexer.h"
#include "./ast.h"
#include <stdio.h>

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
            mode = 1;
        }
        else if(!current->right) {
            current->right = createASTNode(AST_PARAM_NAME);
            mode = 2;
        }
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

    index = parameters->end + 1;

    if(result.tokens[index].type != BRACKETS_OPEN) {
        printf("Error: Excepted function body declaration got %d instead!\n", result.tokens[index - 1].type);
        printf("Dump:\n");
        for(;index < result.size +1; ++index) {
            printf("Index: %d, Type: %d\n", index, result.tokens[index].type);
        }
        return;
    }

    index++;

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
