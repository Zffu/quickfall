/**
 * Quickfall IR Structures.
 */

#include "../utils/hashmap.h"

#ifndef IR_STRUCTS_H
#define IR_STRUCTS_H

/**
 * An IR instruction.
 */
typedef struct IR_INSTRUCTION {

    unsigned char opCode;

    unsigned char* params;
    int paramCount;

} IR_INSTRUCTION;

/**
 * An IR basic block.
 */
typedef struct IR_BASIC_BLOCK {

    IR_INSTRUCTION** instructions;
    int instructionCount;
    int allocatedSize;

} IR_BASIC_BLOCK;

/**
 * An IR function.
 */
typedef struct IR_FUNCTION {

    char* funcName;

    IR_BASIC_BLOCK** blocks;
    int blockCount;

    unsigned char* paramTypes;
    int parameterCount;

} IR_FUNCTION;


#endif