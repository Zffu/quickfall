/**
 * The parser of Quickfall.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../lexer/lexer.h"
#include "../lexer/tokens.h"

/**
 * <p>Runs the parser of the provided LexerResult.
 */
void runParser(struct LexerResult result) {
    struct Token* content = malloc((result.size - 2) * sizeof(struct Token));
    int inside = 0;

    for(int i = 0; i < result.size; ++i) {
        struct Token token = result.tokens[i];
        
        if(token.type == PAREN_OPEN || token.type == BRACKETS_OPEN || token.type == ARRAY_OPEN) {
            inside = 1;
        }
    }

    if(inside == 1) {
        printf("Error: A token group wasn't closed before the end of the Token stream!");
    }
}
