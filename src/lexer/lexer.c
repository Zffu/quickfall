/**
 * The lexer of Quickfall
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./tokens.h"
#include "../utils/hashes.h"

/**
 * The result of the lexer execution.
 */
struct LexerResult {
    int size;
    struct Token tokens[1024];
};

/**
 * Sets the token type of the currently selected token in the LexerResult with the provided token type.
 */
void pushToken(struct LexerResult* result, enum TokenType type) {
    result->tokens[result->size].type = type;
    result->size++;
}

/**
 * Runs the lexer on the provided string and returns the parsed tokens.
 */
struct LexerResult runLexer(char string[]) {
    struct LexerResult result;
    result.size = 0;

    result->tokens = malloc(sizeof(struct Token) * 1024);
    
    const int len = strlen(string);
    for(int i = 0; i < len; ++i) {
        const char c = string[i];

        if (c == ' ' || c == '\t' || c == '\n') {
            continue;
        } else if (isdigit(c)) {
            int numLen = 0;
            char numStr[32] = {0};
            
            while (i < len && (isdigit(string[i]) || string[i] == '.')) {
                numStr[numLen++] = string[i++];
            }
            i--;
            
            struct Token token;
            token.type = NUMBER;
	    token.value = numStr;

            result.tokens[result.size++] = token;
            continue;
        } else if (c == '"') {
            int numLen = 0;
            char strValue[longestKeywordSize] = {0};
            i++;
            
            while (i < len && string[i] != '"') {
                strValue[numLen++] = string[i++];
            }
            
            struct Token token;
            token.type = STRING;
	    token.value = strValue;

            result.tokens[result.size++] = token;
            continue;
        } else if (isalpha(c)) {
            int wordLen = 0;
            char word[longestKeywordSize] = {0};
            
            while (i < len && (isalnum(string[i]) || string[i] == '_')) {
                word[wordLen++] = string[i++];
            }
            i--;
            
            struct Token token;
            
            if (strcmp(word, "func") == 0) {
                token.type = FUNCTION;
            } else if (strcmp(word, "true") == 0 || strcmp(word, "false") == 0) {
                token.type = BOOLEAN_VALUE;
            } else if (strcmp(word, "null") == 0) {
                token.type = NU;
            } else if(strcmp(word, "use") == 0) {
                token.type = USE;
            } else if(strcmp(word, "var") == 0) {
		token.type = VAR;
	    }
            else {
                token.type = KEYWORD;
            }
            
	    token.value = word;
            result.tokens[result.size++] = token;
            continue;
        }
        
        switch(c) {
            case '{': pushToken(&result, BRACKETS_OPEN); break;
            case '}': pushToken(&result, BRACKETS_CLOSE); break;
            case '(': pushToken(&result, PAREN_OPEN); break;
            case ')': pushToken(&result, PAREN_CLOSE); break;
            case '[': pushToken(&result, ARRAY_OPEN); break;
            case ']': pushToken(&result, ARRAY_CLOSE); break;
            case ';': pushToken(&result, SEMICOLON); break;
            case ',': pushToken(&result, COMMA); break;
            case '=': pushToken(&result, DECLARE); break;
	    case '?':
		pushToken(&result, NONE); 
		result.tokens[result.size - 1].value[0] = '?';	
		break;
	    case '+':
	    case '-':
	    case '/':
	    case '*':
		pushToken(&result, MATH_OP);
		result.tokens[result.size - 1].value[0] = c;
		break;
        }
    }

    if (result.size > 0 && strlen(result.tokens[result.size - 1].value) == 0) {
        result.size--;
    }

    return result;
}
