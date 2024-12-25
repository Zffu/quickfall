/**
 * Quickfall IR Structures.
 */

#ifndef IR_STRUCTS_H
#define IR_STRUCTS_H

/**
 * An IR instruction.
 */
typedef struct {

    unsigned char* opCode;

    void* params;
    int paramCount;

} IR_INSTRUCTION;

/**
 * An IR basic block.
 */
typedef struct {

    IR_INSTRUCTION* instructions;
    int instructionCount;

} IR_BASIC_BLOCK;

/**
 * An IR function.
 */
typedef struct {

    char* funcName;

    IR_BASIC_BLOCK* blocks;
    int blockCount;

} IR_FUNCTION;

#endif