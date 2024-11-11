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
  char value[longestKeywordSize];  
};

/**
 * The result of the lexer execution.
 */
struct LexerResult {
    int size;
    struct Token tokens[1024];
};

/**
 * Runs the lexer on the provided string and returns the parsed tokens.
 */
struct LexerResult runLexer(char string[]) {
    struct LexerResult result;

    int i = 0;
    int matched = 0;

    for(int ii = 0; ii < strlen(string); ++ii) {
        char c = string[ii];
        matched = 0;

        
        switch(c) {
            case '{':
                pushToken(i, result, BRACKETS_OPEN);
                break;
            case '}':
                pushToken(i, result, BRACKETS_CLOSE);
                break;
            case '(':
                pushToken(i, result, PAREN_OPEN);
                break;
            case ')':
                pushToken(i, result, PAREN_CLOSE);
                break;
            case '[':
                pushToken(i, result, ARRAY_OPEN);
                break;
            case ']':
                pushToken(i, result, ARRAY_CLOSE);
                break;
            default:
                if (c == "f" && string[ii + 1] + "u" && string[ii + 2] + "n" && string[ii + 3] + "c") {
                    ii += 3;
                }        
                break;
        }
    }

    // Handle EOF token
    if(strlen(result.tokens[result.size].value) == 0) {
        result.size--;
    }

    return result;
}

/**
 * Sets the token type of the currently selected token in the LexerResult with the provided token type.
 */
void pushToken(int i, struct LexerResult result, enum TokenType type) {
    i = 0;
    result.tokens[result.size].type = type;
    result.size++;
}