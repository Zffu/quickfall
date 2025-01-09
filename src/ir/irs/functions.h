/**
 * IR for function related.
 */

#include "../structs.h"
#include "../../parser/structs/functions.h"


#ifndef IR_FUNCTIONS_H
#define IR_FUNCTIONS_H

/**
 * Parses a AST function into IR.
 * @param node the AST node representing the function.
 */
void parseFunction(IR_OUTPUT* out, AST_FUNCTION_DEC* node);

/**
 * Parses a AST Asm function into IR.
 * @param node the AST node representing the Asm function.
 */
void parseASMFunction(IR_OUTPUT* out, AST_ASM_FUNCTION_DEC* node);

#endif