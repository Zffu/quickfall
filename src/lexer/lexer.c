/**
 * The lexer of Quickfall
 */

#include <string.h>
#include "./tokens.c"
#include "../utils/hashes.c"

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

    int branchCount = 0;

    // Put the max token size here
    char stack[highestTokenLength];
    int stackIndex;

    for(int i = 0; i < strlen(text); ++i) {
        char c = text[i];

        if(c == ' ') {
            struct Token newToken;
            newToken.type = tokenHash(stack);
            newToken.value = stack;
            stackIndex = 0;

            if(branchCount == 0) {
                token.next = newToken;
                branch = newToken;
            }
            else {
                branch.next = newToken;
                branch = newToken;
            }

            branchCount++;
        }
        else {
            stack[stackIndex] = c;
            stackIndex++;

            if(stackIndex == highestTokenLength) {
                struct Token newToken;
                newToken.type = tokenHash(stack);
                newToken.value = stack;

                if(branchCount == 0) {
                    token.next = newToken;
                    branch = newToken;
                }
                else {
                    branch.next = newToken;
                    branch = newToken;
                }

                branchCount++;
            }
        }
    } 

    return token;
}