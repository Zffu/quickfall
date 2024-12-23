/**
 * Quickfall PE executable compiling.
 */

#include <stdio.h>
#include <stdint.h>

#ifndef COMPILER_PE
#define COMPILER_PE

/**
 * Compiles into PE format.
 */
void compilePE(FILE* fptr, uint8_t program[], int programSize);

#endif
