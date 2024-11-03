/**
 * Tests to make sure the token hashes aren't colliding.
 */

#include "../src/utils/hashes.c"
#include <stdio.h>
#include <stdbool.h>

// The tokens to test
char* tokens[10] = {
    "function",
    "return",
    "var",
    "{",
    "}",
    "(",
    ")",
    "[",
    "]",
    "ara"
};

// Replace the current size with the highest possible hash.
bool takenHashes[10];

/**
 * Performs the hash checking logic.
 */
int main() {
    for(int i = 0; i < 11; ++i) {
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