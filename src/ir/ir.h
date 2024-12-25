/**
 * The Intermediate Representation of Quickfall Code.
 */

#ifndef IR2_H
#define IR2_H

#include "./structs.h"

/**
 * Appends an IR instruction into the basic block.
 * @parma block the IR basic block.
 * @param opCode the operation code of the instruction.
 * @param params the parameters of the operation.
 * @param paramsCount the count of the parameters of the operation.
 */
void appendInstruction(IR_BASIC_BLOCK block, unsigned char opCode, void* params, int paramsCount);

#endif