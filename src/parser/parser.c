/**
 * The parser of Quickfall.
 */

#include "../lexer/lexer.h"
#include <stdio.h>

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

void parseFunctionDeclaration(struct LexerResult result, int index) {
    for(int i = index + 3; i < result.size; ++i) {
        struct Token t = result.tokens[i];

        if(t.type == PAREN_CLOSE) break;

        printf("Token in parameters: %d\n", t.type);
    }
}