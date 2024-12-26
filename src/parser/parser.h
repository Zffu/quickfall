/**
 * The Quickfall Parser & AST Generator.
 */

#include "./ast.h"
#include "./structs/tree.h"

#include "../lexer/lexer.h"

#ifndef PARSER_H
#define PARSER_H

/**
 * Parses the Lexer result into an AST root.
 * @param result the Lexer result.
 * @param type the output AST type.
 */
void* parseRoot(LEXER_RESULT result, AST_TYPE type);

#endif