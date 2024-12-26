/**
 * AST structure definitions for function related ASTs.
 */

#ifndef FUNCTIONS_STRUCT_H
#define FUNCTIONS_STRUCT_H

/**
 * The function parameter structure.
 */
typedef struct {

    unsigned char* type; // The datatype in bytes.
    char* name; // The name of the parameter

} AST_PARAMETER;


/**
 * The function declaration structure.
 */
typedef struct {
    unsigned char type; // The type of the AST node (unused.)
    void* next;
    int endingIndex;

    char* funcName;
    unsigned char* returnType;

    AST_PARAMETER* parameters;
    int parameterIndex;

    void* body;

} AST_FUNCTION_DEC;


/**
 * The ASM function declaration structure.
 */
typedef struct {
    unsigned char type; // The type of the AST node (unused.)
    void* next; 
    int endingIndex;

    char* funcName;

    AST_PARAMETER* parameters;
    int parameterIndex;

    unsigned char* buff; // The content buffer of the function.
    int buffIndex; // The size of buff.

} AST_ASM_FUNCTION_DEC;


/**
 * The function invocation structure.
 */
typedef struct {
    unsigned char type;
    void* next;
    int endingIndex;

    void* arguments;
    int argumentIndex;
} AST_FUNCTION_INVOKE;

#endif