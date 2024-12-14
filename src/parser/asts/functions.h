/**
 * Function-related AST parsing.
 */

#include "../../lexer/lexer.h"

#include "../ast.h"

#ifndef AST_FUNC_H
#define AST_FUNC_H

/**
 * Parse the parameters from a function defintition (for example).
 * @param result the lexer result.
 * @param index the starting index of the parsing.
 */
AST_NODE* parseParameters(struct LexerResult result, int index);

/**
 * Parses the arguments from a function call (for example).
 * @param result the lexer result.
 * @param index the starting index of the parsing.
 */
AST_NODE* parseArguments(struct LexerResult result, int index);

/**
 * Parses a function declaration.
 * @param result the lexer result.
 * @param index the starting index of the parsing.
 */
AST_NODE* parseFunctionDeclaration(struct LexerResult result, int index);

#endif
