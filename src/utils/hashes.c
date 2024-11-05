/**
 * Hashmap related utilities for Quickfall.
 */

#include <string.h>

/**
 * Generates a hash for a lexar token. Currently compromisable
 */
int tokenHash(char* token) {
    int len = strlen(token);

    printf("TOken: %s", token);

    if(len == 1) {
        printf("Mawing");
    }

    return len;
}