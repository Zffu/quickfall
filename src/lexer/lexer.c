/**
 * The lexer of Quickfall
 */

/**
 * A token that was parsed by the Lexer.
 */
typedef struct Token {
    struct Token next;
    int type;
} Token;
