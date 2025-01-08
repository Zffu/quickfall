/**
 * QuickAssembly Value types parsing.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Parses a 32-bit integer into bytes.
 * @param buff the buff to append the bytes to.
 * @param startIndex the starting index of where to append the bytes.
 * @param str the string containing the integer.
 */
void parseInt32(unsigned char* buff, int startIndex, char* str) {
    int i = atoi(str);

    buff[startIndex] = (i >> 24) & 0xFF;
    buff[startIndex + 1] = (i >> 16) & 0xFF;
    buff[startIndex + 2] = (i >> 8) & 0xFF;
    buff[startIndex + 3] = i & 0xFF;
}


/**
 * Parses a variable name.
 * @param buff the buff to append the bytes to.
 * @param startIndex the starting index of where to append the bytes.
 * @param str the string containing the variable name.
 */
int parseVariableName(unsigned char* buff, int startIndex, char* str) {
    if(str[0] != '%') {
        printf("Error: Variable names must start with %%! Got %s\n", str);
        return -1;
    }

    --startIndex;

    int i = 1;

    while(str[i] != '\0') {
        buff[startIndex + i] = str[i];
        ++i;
    }

    str[i] = '\0';
    ++i;

    return i + startIndex;
}