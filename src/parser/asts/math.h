/**
 * Math ASTs for the Quickfall parser.
 */

#include "../ast.h"

/**
 * Parses the mathematical operation.
 * @param result the lexer result.
 * @param index the starting index.
 */
AST_NODE* parseMathematicalOpNode(struct LexerResult result, int index);

