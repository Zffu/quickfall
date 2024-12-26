/**
 * AST structure definitions for function related ASTs.
 */

#ifndef FUNCTIONS_STRUCT_H
#define FUNCTIONS_STRUCT_H

/**
 * The function declaration structure.
 */
typedef struct {
    unsigned char type; // The type of the AST node (unused.)
    void* next;

    char* funcName;
    unsigned char* returnType;

    void* body;

} AST_FUNCTION_DEC;

#endif