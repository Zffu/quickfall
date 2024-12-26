/**
 * AST structure definitions for value related ASTs.
 */

#ifndef VALUES_STRUCTURES_H
#define VALUES_STRUCTURES_H

/**
 * The AST structure of a value.
 */
typedef struct AST_VALUE {
    unsigned char astType;
    void* next;
    int endingIndex;

    unsigned char* valueType;
    void* value;
} AST_VALUE;

#endif