/**
 * The token hash -> token type table.
 */

const int highestTokenHash = 10;
const int highestTokenLength = 8;


/**
 * The token types.
 */
enum TokenType {
    FUNCTION = 1,
    RETURN = 2,
    VAR = 3
};

int types[highestTokenHash] = {};

/**
 * Inits the tables of tokens
 */
void initTypes() {
    types[8] = FUNCTION;
    types[6] = RETURN;
    types[3] = VAR;
}
