/**
 * The parser of QuickAssembly. The inline assembly of Quickfall.
 */

#include "../../parser/structs/functions.h"
#include "../../ir/structs.h"

#ifndef QASM_PARSER_H
#define QASM_PARSER_H

/**
 * Parses QuickAssembly instructions.
 */
void parseQAsmInstructions(IR_BASIC_BLOCK* block, char* buff, int size);

/**
 * Parses a QuickAssembly instruction.
 */
IR_INSTRUCTION* parseInstruction(char** buff, int size);

#endif