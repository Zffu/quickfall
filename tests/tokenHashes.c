/**
 * Tests to make sure the token hashes aren't colliding.
 */

#include "../src/utils/hashes.c"
#include <stdio.h>

// The tokens to test
char* tokens[3] = {
    "function",
    "return",
    "var"
};

/**
 * Performs the hash checking logic.
 */
int main() {
    for(int i = 0; i < 3; ++i) {
        printf("Hash: %d\n", tokenHash(tokens[i]));
    }
}