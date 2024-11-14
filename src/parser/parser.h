/**
 * The parser of Quickfall.
 */

#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"

/**
 * A node of the parser, allows for a tree-ish visualization of the parser sub groups.
 */
struct ParserNode {
    struct ParserNode* children;
    struct Token* tokens;
    int childrenIndex;
    int tokensIndex;
};

/**
 * <p>Runs the parser on the provided LexerResult.
 */
void runParser(struct LexerResult result);

#endif