/**
 * The lexer of Quickfall
 */

#include <string.h>
#include "./tokens.c"

/**
 * A token that was parsed by the Lexer.
 */
struct Token {
  struct Token next;
  int type;
  char* value;  
};

// todo: investigate if this is good for performance
struct CharStack {
    struct CharStack next;
    char value;
};

struct Token runLexer(char text[]) {
    struct Token token;
    struct Token branch;

    // Put the max token size here
    char stack[highestTokenLength];
    int stackIndex;

    for(int i = 0; i < strlen(text); ++i) {
        char c = text[i];

        if(c == ' ') {
            struct Token newToken;
            newToken.type = 0;
            newToken.value = stack;
        }
        else {
            stack[stackIndex] = c;
            stackIndex++;
        }
    } 
}