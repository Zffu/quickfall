/**
 * QuickAssembly Value types parsing.
 */

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