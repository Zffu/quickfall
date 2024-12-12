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

struct KeywordResult {
    int count;
    char* keywords[10];
    enum TokenType types[10];
};

void initKeywords();
struct KeywordResult getKeywords(char start);

#endif
