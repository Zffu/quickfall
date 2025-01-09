#include <stdio.h>
#include <ctype.h>

/**
 * Writes a 32 bit integer into the file.
 */
void writeInt32(FILE* fptr, void** buff, int index) {
    fprintf(fptr, " %d", (((unsigned char*)buff[index])[0] << 24) | (((unsigned char*)buff[index])[1] << 16) | (((unsigned char*)buff[index])[2] << 8) | ((unsigned char*)buff[index])[3]);
}

/**
 * Writes a variable name.
 */
int writeVarName(FILE* fptr, void** buff, int index) {
    fprintf(fptr, " %%%s", buff[index]);
}