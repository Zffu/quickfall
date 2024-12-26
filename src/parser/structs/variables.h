/**
 * AST structure definitions for variable related ASTs.
 */

#ifndef VARIABLES_STRUCT_H
#define VARIABLES_STRUCT_H

/**
 * The variable declaration structure.
 */
typedef struct {
    unsigned char astType;
    void* next;

    unsigned char* type;
    char* name;

    unsigned char* value;
} AST_VARIABLE_DEC;

#endif