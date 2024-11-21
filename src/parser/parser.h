/**
 * The parser of Quickfall.
 */

#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"

/**
 * Runs the parser
 */
struct ASTNode* runParser(struct LexerResult result);

#endif