/**
 * Utilities for the Quickfall compiler.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Writes an 8 bit number into the file.
 */
void write8(FILE *file, uint8_t value) {

	printf("Input %d for: %02x\n", value, (value >> 0) & 0xff);

        if (fputc(value, file) == EOF) {
                perror("fputc");
                exit(1);
        }
}

/**
 * Writes an 16 bit number into the file.
 */
void write16(FILE *file, uint16_t value) {
        write8(file, (value >> 0) & 0xff);
        write8(file, (value >> 8) & 0xff);
}

/**
 * Writes an 32 bit number into the file.
 */
void write32(FILE *file, uint32_t value) {
        write8(file, (value >> 0)  & 0xff);
        write8(file, (value >> 8)  & 0xff);
        write8(file, (value >> 16) & 0xff);
        write8(file, (value >> 24) & 0xff);

	printf("32 Input for %d: %02x %02x %02x %02x\n", (value >> 0) & 0xff, (value >> 8) & 0xff, (value >> 16) && 0xff, (value >> 24) & 0xff);
}

/**
 * Writes a string with a 8 bit padding.
 */
void writestr8(FILE *file, char *str) {
        size_t len, i;

        len = strlen(str);
        assert(len <= 8 && "The string must fit in 8 bytes.");

        for (i = 0; i < 8; i++) {
                write8(file, i < len ? str[i] : 0);
        }
}

/**
 * Writes a string with a 16 bit padding.
 */
void writestr16(FILE *file, char *str) {
        size_t len, i;

        len = strlen(str);
        assert(len <= 15 && "The string and terminator must fit in 16 bytes.");

        for (i = 0; i < 16; i++) {
                write8(file, i < len ? str[i] : 0);
        }
}

/**
 * Seeks to offset in a file.
 */
void seek(FILE *file, long offset) {
        if (fseek(file, offset, SEEK_SET) == -1) {
                perror("fseek");
                exit(1);
        }
}

/**
 * Rounds the number to the provided alignment.
 */
uint32_t align_to(uint32_t value, uint32_t alignment) {
        uint32_t remainder = value % alignment;

        if (remainder == 0) {
                return value;
        }

        return value + (alignment - remainder);
}
