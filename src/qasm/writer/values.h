#include <stdio.h>

#ifndef QASM_WRITER_VALUES_H
#define QASM_WRITER_VALUES_H

/**
 * Writes a 32 bit integer into the file.
 */
void writeInt32(FILE* fptr, void** buff, int index);

/**
 * Writes a variable name.
 */
void writeVarName(FILE* fptr, void** buff, int index);

#endif