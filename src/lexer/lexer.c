/**
 * The lexer of Quickfall
 */

#include <stdio.h>
#include <string.h>
#include "./tokens.c"
#include "../utils/hashes.c"

/**
 * A token that was parsed by the Lexer.
 */
struct Token {
  int type;
  char value[highestTokenLength];  
};

struct LexerResult {
    int size;
    struct Token tokens[1024];
};

/**
 * Runs the lexer logic.
 */
struct LexerResult runLexer(char string[]) {
    struct LexerResult result;

    int i = 0;

    for(int ii = 0; ii < strlen(string); ++ii) {
        char c = string[ii];

        if(c == ' ') {
            printf("Spaced i: %d raw: %s\n", i, result.tokens[result.size].value);
            i = 0;
            result.tokens[result.size].type = types[tokenHash(result.tokens[result.size].value)];
            result.size++;

            //memset(stack, 0, sizeof(stack));
        }
        else {
            result.tokens[result.size].value[i] = c;
            i++;

            if(i == highestTokenLength) {
                printf("Excess i: %d raw: %s\n", i, result.tokens[result.size].value);
                i = 0;
                result.tokens[result.size].type = types[tokenHash(result.tokens[result.size].value)];
                result.size++;
            }
        }
    }

    return result;
}
