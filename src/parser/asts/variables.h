/**
 * Parsing for variable related ASTs.
 */

#include "../structs/variables.h"

#include "../../lexer/lexer.h"

#ifndef VARIABLES_ASTS_H
#define VARIABLES_ASTS_H

/**
 * Parses a variable declaration.
 * @param result the Lexer result.
 * @param index the index where the parsing needs to start.
 */
AST_VARIABLE_DEC parseVariableDeclaration(LEXER_RESULT result, int index);

/**
 * Parses a variable modification.
 * @param result the Lexer result.
 * @param index the index where the parsing needs to start.
 */
AST_VARIABLE_MOD parseVariableModification(LEXER_RESULT result, int index);

#endif