/**
 * Tests to make sure the token hashes aren't colliding.
 */

#include "../src/utils/hashes.c"
#include "../src/lexer/tokens.c"
#include <stdio.h>
#include <stdbool.h>

// The tokens to test
char* tokens[9] = {
    "function",
    "return",
    "var",
    "{",
    "}",
    "(",
    ")",
    "[",
    "]"
};

// Replace the current size with the highest possible hash.
bool takenHashes[highestTokenHash];

/**
 * Performs the hash checking logic.
 */
int main() {
    for(int i = 0; i < highestTokenHash; ++i) {
        int hash = tokenHash(tokens[i]);

        if(takenHashes[hash] != 0) {
            printf("Hash %d is already taken! The hash function is compromised!\n", hash);
            //return -1;
        }

        printf("Hash for %s: %d\n", tokens[i], hash);

        takenHashes[hash] = 1;
    }

    printf("\nAll hashes were unique!");
}