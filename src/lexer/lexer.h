#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "./tokens.h"

/**
 * Represents a single token from lexical analysis
 */
struct Token {
    int type;
    char value[32];  // Using 32 as longestKeywordSize
};

/**
 * Contains the results of lexical analysis
 */
struct LexerResult {
    int size;
    struct Token tokens[1024];
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
