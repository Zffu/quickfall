/**
 * IR for variable related.
 */

#include "../../parser/structs/variables.h"

#include "../ir.h"

#ifndef IR_VARIABLES_H
#define IR_VARIABLES_H

/**
 * Parses a variable declaration.
 * @param block the IR basic block to append to.
 * @param node the AST node representing the variable.
 */
inline void parseVariableDeclaration(IR_BASIC_BLOCK* block, AST_VARIABLE_DEC* node);

/**
 * Parses a variable modification.
 * @param block the IR basic block to append to.
 * @param node the AST node representing the variable.
 */
inline void parseVariableModification(IR_BASIC_BLOCK* block, AST_VARIABLE_MOD* node);

#endif