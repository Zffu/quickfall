/**
 * The Intermediate Representation of Quickfall Code.
 */

#ifndef IR2_H
#define IR2_H

#include "./instructions.h"
#include "./structs.h"

#include "../parser/structs/variables.h"
#include "../parser/structs/functions.h"

#include "../parser/ast.h"

/**
 * Appends an IR instruction into the basic block.
 * @parma block the IR basic block.
 * @param opCode the operation code of the instruction.
 * @param params the parameters of the operation.
 * @param paramsCount the count of the parameters of the operation.
 */
void appendInstruction(IR_BASIC_BLOCK block, IR_INSTRUCTION_CODE code, unsigned char params[], int paramsCount);

/**
 * Parses a AST function into IR.
 * @param node the AST node representing the function.
 */
IR_FUNCTION parseFunction(AST_FUNCTION_DEC* node);

#endif