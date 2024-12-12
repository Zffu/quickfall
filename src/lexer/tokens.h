#ifndef TOKENS_H
#define TOKENS_H

#define longestKeywordSize 32
#define smallestKeywordSize 4

enum TokenType {
    FUNCTION,
    RETURN,
    VAR,
    BRACKETS_OPEN,
    BRACKETS_CLOSE,
    PAREN_OPEN,
    PAREN_CLOSE,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    NUMBER,
    STRING,
    BOOLEAN_VALUE,
    NU,
    KEYWORD,
    SEMICOLON,
    COMMA,
    DECLARE,
    USE,
    NONE,
    MATH_OP
};

#endif
