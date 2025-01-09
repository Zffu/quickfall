/**
 * Parsing for value related ASTs.
 */

#include "../structs/values.h"

#include "../../lexer/lexer.h"

#include "../../lib/types.h"

#ifndef VALUES_AST_H
#define VALUES_AST_H

/**
 * Parses an AST value on the lexer result.
 * @param result the Lexer result.
 * @param index the index of the start of the parsing.
 * @param exceptedType The excepted type of token.
 */
AST_VALUE* parseASTValue(LEXER_RESULT result, int index, LIB_TYPES exceptedType);

/**
 * Parses an actual expression as value instead of just one token.
 * @param result the Lexer result.
 * @param index the index of the start of the parsing.
 * @param exceptedType The excepted type of token.
 */
void* parseValueGroup(LEXER_RESULT result, int index, LIB_TYPES exceptedType);

#endif