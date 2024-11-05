/**
 * The token hash -> token type table.
 */

#define highestTokenHash 10
#define highestTokenLength 8

/**
 * The token types.
 */
enum TokenType {
    FUNCTION = 1,
    RETURN = 2,
    VAR = 3,
    BRACKETS_OPEN = 4,
    BRACKETS_CLOSE = 5,
    PAREN_OPEN = 6,
    PAREN_CLOSE = 7,
    ARRAY_OPEN = 8,
    ARRAY_CLOSE = 9
};

int types[highestTokenHash] = {};
char* rawValues[highestTokenHash] = {};

/**
 * Inits the tables of tokens
 */
void initTypes() {
    types[8] = FUNCTION;
    types[6] = RETURN;
    types[3] = VAR;
    
    rawValues[8] = "function";
    rawValues[6] = "return";
    rawValues[3] = "var";
}
