/**
 * Data related to tokens
 */

#define longestKeywordSize 4
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

    KEYWORD = 10
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
            result.keywords[0] = "func";
            result.types[0] = FUNCTION;
            result.count++;
            break;
    }

    return result;
}