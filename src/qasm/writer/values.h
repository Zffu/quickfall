#include <stdio.h>

#ifndef QASM_WRITER_VALUES_H
#define QASM_WRITER_VALUES_H

/**
 * Writes a 32 bit integer into the file.
 */
void writeInt32(FILE* fptr, unsigned char* buff, int startingIndex);

/**
 * Writes a variable name.
 */
int writeVarName(FILE* fptr, unsigned char* buff, int startIndex);

#endif