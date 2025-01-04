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
IR_FUNCTION parseFunction(AST_FUNCTION_DEC* node);

#endif