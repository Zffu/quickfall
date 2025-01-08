#include <stdio.h>
#include <ctype.h>

/**
 * Writes a 32 bit integer into the file.
 */
void writeInt32(FILE* fptr, unsigned char* buff, int startingIndex) {
    fprintf(fptr, " %d", (buff[startingIndex] << 24) | (buff[startingIndex + 1] << 16) | (buff[startingIndex + 2] << 8) | buff[startingIndex + 3]);
}

/**
 * Writes a variable name.
 */
int writeVarName(FILE* fptr, unsigned char* buff, int startIndex) {
    fprintf(fptr, " %%");
    buff += startIndex;

    int i = startIndex;
    char c;
    while(c = *buff++) {
        if(c == '\0' || !isalpha(c)) break;
        printf("%c", c);
        fputc(c, fptr);
        ++i;
    }

    return i;
}