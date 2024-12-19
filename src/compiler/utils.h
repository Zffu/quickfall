/**
 * Utilities for the Quickfall Compiler.
 */

#include <stdint.h>

#ifndef COMPILER_UTILS_H
#define COMPILER_UTILS_H

void write8(FILE* fptr, uint8_t value);
void write16(FILE* fptr, uint16_t value);
void write32(FILE* fptr, uint32_t value);

#endif
