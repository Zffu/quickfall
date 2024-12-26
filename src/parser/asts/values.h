/**
 * Parsing for value related ASTs.
 */

#include "../structs/values.h"

#include "../../lexer/lexer.h"

#ifndef VALUES_AST_H
#define VALUES_AST_H

/**
 * Parses an AST value on the lexer result.
 * @param result the Lexer result.
 * @param index the index of the start of the parsing.
 */
AST_VALUE parseValue(LEXER_RESULT result, int index);

#endif