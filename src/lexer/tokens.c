/**
 * The token hash -> token type table.
 */

/**
 * The token types.
 */
enum TokenType {
    FUNCTION = 1,
    RETURN = 2,
    VAR = 3
};

int types[10] = {};

/**
 * Inits the tables of tokens
 */
void initTypes() {
    types[8] = FUNCTION;
    types[6] = RETURN;
    types[3] = VAR;
}
