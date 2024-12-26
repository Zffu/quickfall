/**
 * The Quickfall Parser & AST Generator.
 */

#include "./structs/tree.h"

#include "../lexer/lexer.h"

#ifndef PARSER_H
#define PARSER_H

/**
 * Parses the Lexer result into an AST root.
 * @param result the Lexer result.
 */
AST_ROOT_TREE parseRoot(LEXER_RESULT result);

#endif