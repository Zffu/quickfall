/**
 * Variable-related AST parsing.
 */

#include "../ast.h"

#include "../../lexer/lexer.h"

#ifndef AST_VARIABLES_H
#define AST_VARIABLES_H

/**
 * Parses a variable value.
 * @param result the lexer result.
 * @param index the starting index.
 */
AST_NODE* parseVariableValue(LEXER_RESULT result, int index);

/**
 * Parses a variable declaration.
 * @param result the lexer result.
 * @param index the starting index.
 */
AST_NODE* parseVariableDeclaration(LEXER_RESULT result, int index);

#endif
