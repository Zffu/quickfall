/**
 * The parser of Quickfall.
 */

#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"


struct ASTNode* parseParameters(struct LexerResult result, int index);
void parseFunctionDeclaration(struct LexerResult result, int index);

void runParser(struct LexerResult result);

#endif