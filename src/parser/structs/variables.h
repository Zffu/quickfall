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
    int endingIndex;

    unsigned char* type;
    char* name;

    unsigned char* value;
} AST_VARIABLE_DEC;


/**
 * The variable modification structure.
 */
typedef struct {
    unsigned char type;
    void* next;
    int endingIndex;

    char* name;
    unsigned char* value;
} AST_VARIABLE_MOD;

#endif