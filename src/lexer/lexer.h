#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "./tokens.h"

/**
 * Contains the results of lexical analysis
 */
typedef struct {
    int size;
    TOKEN* tokens;
} LEXER_RESULT;

/**
 * Performs lexical analysis on an input string
 * Returns a LexerResult containing the tokens
 */
LEXER_RESULT runLexer(char* input, int size);

/**
 * Adds a token to the LexerResult
 * @param result The LexerResult to add the token to
 * @param type The type of the token to add
 */
void pushToken(LEXER_RESULT* result, TOKEN_TYPE type);

#endif
