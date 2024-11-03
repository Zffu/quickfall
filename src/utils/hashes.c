/**
 * Hashmap related utilities for Quickfall.
 */

#include <string.h>

/**
 * Generates a hash for a lexar token. Currently compromisable
 */
int tokenHash(char* token) {
    int len = strlen(token);
    if(len == 1) {
        return (int)(token[0]) - 40;
    }

    int hash = 0;
    for(int i = 0; i < len; ++i) {
        hash += (int)token[i] * (i / 10 + 0.1);
    }
    return hash;
}