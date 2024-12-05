/**
 * The parser of Quickfall.
 */

#include "../lexer/lexer.h"
#include "./ast.h"

#ifndef PARSER_2_H
#define PARSER_2_H

/**
 * Parses the lexer tokens into nodes starting from the index.
 * @param result the LexerResult provided by the lexer.
 * @param index the starting index.
 */
AST_NODE* parseNodes(struct LexerResult result, int index);

#endif
