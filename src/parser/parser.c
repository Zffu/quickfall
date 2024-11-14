/**
 * The parser of Quickfall.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../lexer/lexer.h"
#include "../lexer/tokens.h"

/**
 * A node of the parser, allows for a tree-ish visualization of the parser sub groups.
 */
struct ParserNode {
    struct ParserNode* children;
    struct Token* tokens;
    int childrenIndex;
    int tokensIndex;
};

/**
 * <p>Runs the parser of the provided LexerResult.
 */
void runParser(struct LexerResult result) {
    struct ParserNode root;
    
    struct ParserNode* branch = &root;
    struct ParserNode* latest = &root;

    for(int i = 0; i < result.size; ++i) {
        struct Token token = result.tokens[i];

        switch(token.type) {
            case PAREN_OPEN:
            case BRACKETS_OPEN:
            case ARRAY_OPEN:
                if(latest->children == NULL) {
                    latest->children = malloc((result.size - 2) * sizeof(struct Token));
                }

                latest->childrenIndex++;
                branch = latest;
                latest = &latest->children[latest->childrenIndex];
                break;
            case PAREN_CLOSE:
            case BRACKETS_CLOSE:
            case ARRAY_CLOSE:
                if(branch != NULL) {
                    latest = branch;
                }
                break;
            default:
                latest->tokens[latest->tokensIndex] = token;
                latest->tokensIndex++;
        }

    }

    printf("sjjduios");
}
