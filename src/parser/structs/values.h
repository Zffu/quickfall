/**
 * AST structure definitions for value related ASTs.
 */

#ifndef VALUES_STRUCTURES_H
#define VALUES_STRUCTURES_H

/**
 * The AST structure of a value.
 */
typedef struct {
    unsigned char astType;

    void* value;
} AST_VALUE;

#endif