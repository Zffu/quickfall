/**
 * The Intermediate Representation of Quickfall Code.
 */

#ifndef IR2_H
#define IR2_H

#include "./instructions.h"
#include "./structs.h"

#include "../parser/structs/variables.h"
#include "../parser/structs/functions.h"
#include "../parser/structs/tree.h"

#include "../parser/ast.h"

/**
 * Appends an IR instruction into the basic block.
 * @param block the IR basic block.
 * @param instruction the instruction.
 */
void pushInstruction(IR_BASIC_BLOCK* block, IR_INSTRUCTION* instruction);

/**
 * Appends an IR instruction into the basic block.
 * @parma block the IR basic block.
 * @param opCode the operation code of the instruction.
 * @param params the parameters of the operation.
 * @param paramsCount the count of the parameters of the operation.
 */
void appendInstruction(IR_BASIC_BLOCK* block, IR_INSTRUCTION_CODE code, void** params, int paramsCount);

/**
 * Converts the AST tree into IR.
 */
IR_OUTPUT* parseIR(AST_TREE_BRANCH* node);

#endif