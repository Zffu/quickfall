/**
 * Data related to tokens
 */

#define longestKeywordSize 32 // Pumped up to handle longer values like numbers
#define smallestKeywordSize 4

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
    ARRAY_CLOSE = 9,
    NUMBER = 10,
    STRING = 11,
    BOOLEAN = 12,
    NU = 13, // Null is a keyword but also a value
    
    KEYWORD = 14
};

int keywords[6];
char* rawKeywords[6];

/**
 * Instantiates the keywords array.
 */
static void initKeywords() {
    keywords[4] = FUNCTION;
    keywords[3] = KEYWORD;
    keywords[2] = KEYWORD;
    keywords[1] = KEYWORD;
    keywords[0] = KEYWORD;

    rawKeywords[4] = "func";
    rawKeywords[3] = "func";
    rawKeywords[2] = "func";
    rawKeywords[1] = "func";
    rawKeywords[0] = "func";
}

struct KeywordResult {
    int count;
    char* keywords[10];
    enum TokenType types[10];
};

struct KeywordResult getKeywords(char start) {
    struct KeywordResult result;
    result.count = 0;

    switch(start) {
        case 'f':
            // Return both possibilities for 'f' prefix
            result.keywords[0] = "func";
            result.types[0] = FUNCTION;
            result.keywords[1] = "false";
            result.types[1] = BOOLEAN;
            result.count = 2;
            break;
        case 't':
            result.keywords[0] = "true";
            result.types[0] = BOOLEAN;
            result.count = 1;
            break;
    }

    return result;
}