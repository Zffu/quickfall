/**
 * Math ASTs for the Quickfall parser.
 */

#include "../ast.h"

#ifndef AST_MATH_H
#define AST_MATH_H

/**
 * Parses the mathematical operation.
 * @param result the lexer result.
 * @param index the starting index.
 */
AST_NODE* parseMathematicalOpNode(struct LexerResult result, int index);

#endif