#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "./tokens.h"

/**
 * Contains the results of lexical analysis
 */
struct LexerResult {
    int size;
    struct Token* tokens;
};

/**
 * Performs lexical analysis on an input string
 * Returns a LexerResult containing the tokens
 */
struct LexerResult runLexer(const char* input);

/**
 * Adds a token to the LexerResult
 * @param result The LexerResult to add the token to
 * @param type The type of the token to add
 */
void pushToken(struct LexerResult* result, enum TokenType type);

#endif
