/**
 * The Intermediate Representation of Quickfall Code.
 */

#include "./instructions.h"
#include "./structs.h"

/**
 * Appends an IR instruction into the basic block.
 * @parma block the IR basic block.
 * @param opCode the operation code of the instruction.
 * @param params the parameters of the operation.
 * @param paramsCount the count of the parameters of the operation.
 */
void appendInstruction(IR_BASIC_BLOCK block, IR_INSTRUCTION_CODE code, void* params, int paramsCount) {
    IR_INSTRUCTION instruction = {0};

    instruction.opCode = code;
    instruction.params = params;
    instruction.paramCount = paramsCount;

    block.instructions[block.instructionCount] = instruction;
    block.instructionCount++;
}