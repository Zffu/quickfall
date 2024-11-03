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
  char* value;  
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

    char stack[highestTokenLength];
    int i;

    for(int ii = 0; ii < strlen(string); ++ii) {
        char c = string[ii];

        if(c == ' ') {
            i = 0;
            struct Token newToken;
            newToken.type = types[tokenHash(stack)];
            newToken.value = stack;
            result.tokens[result.size] = newToken;
            result.size++;
        }
        else {
            stack[i] = c;
            ++i;

            if(i == highestTokenLength) {
                i = 0;
                struct Token newToken;
                newToken.type = types[tokenHash(stack)];
                newToken.value = stack;
                result.tokens[result.size] = newToken;
                result.size++;
            }
        }
    }

    if(i > 0) {
        struct Token newToken;
        newToken.type = types[tokenHash(stack)];
        newToken.value = stack;
        result.tokens[result.size] = newToken;
        result.size++;
    }

    return result;
}
