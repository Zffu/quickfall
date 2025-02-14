#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    ASM_FUNCTION,
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
    MATH_OP,

    TYPE_INT32,
    TYPE_INT24,
    TYPE_INT16,
    TYPE_INT8
} TOKEN_TYPE;

/**
 * An lexer token generated by the Lexer.
 */
typedef struct {
	TOKEN_TYPE type;
	char* value;
} TOKEN;


#endif
