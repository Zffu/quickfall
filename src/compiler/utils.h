/**
 * Utilities for the Quickfall Compiler.
 */

#include <stdint.h>

#ifndef COMPILER_UTILS_H
#define COMPILER_UTILS_H

/**
 * Writes an 8 bit number into the file.
 */
void write8(FILE* fptr, uint8_t value);

/**
 * Writes an 16 bit number into the file.
 */
void write16(FILE* fptr, uint16_t value);

/**
 * Writes a 32 bit number into the file.
 */
void write32(FILE* fptr, uint32_t value);

/**
 * Writes a string with a 8 bit padding.
 */
void writestr8(FILE* fptr, char* str);

/**
 * Writes a string with a 16 bit padding.
 */
void writestr16(FILE* fptr, char* str);

/**
 * Seeks to offset in a file.
 */
void seek(FILE* fptr, long offset);

#endif
