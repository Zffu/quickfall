/**
 * The lexer of Quickfall
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./lexer.h"
#include "./tokens.h"

#include "../utils/hashes.h"

/**
 * Sets the token type of the currently selected token in the LexerResult with the provided token type.
 */
void pushToken(struct LexerResult* result, enum TokenType type) {
    result->tokens[result->size].type = type;
    result->size++;
}

struct LexerResult runLexer(char* string) {
	struct LexerResult result;
	result.size = 0;

	result.tokens = malloc(sizeof(struct Token) * 1024);

	char c;

	while(c = *string++) {

		int buffLen = 32;
		char* buff = malloc(buffLen);

		if(c == ' ' || c == '\t' || c == '\n') {
			continue;
		} else if (isdigit(c)) {
			int numLen = 0;

			while(isdigit(c) || c == 'x') {
				buff[numLen] = c;
				numLen++;

				c = *string++;
			}

			pushToken(&result, NUMBER);
			result.tokens[result.size - 1].value = buff;

		} else if (c == '\"') {
			int strLen = 0;

			while(c != '\"') {
				buff[strLen] = c;
				strLen++;

				c = *string++;
			}

			pushToken(&result, STRING);
			result.tokens[result.size - 1].value = buff;

		} else if(isalpha(c)) {
			int keywordLen = 0;
			
			while(isalpha(c)) {
				buff[keywordLen] = c;
				keywordLen++;

				c = *string++;
			}

			if(strcmp(buff, "func") == 0) {
				pushToken(&result, FUNCTION);
			}
			else if(strcmp(buff, "asmf") == 0) {
				pushToken(&result, ASM_FUNCTION);
			}
			else if(strcmp(buff, "true") == 0 || strcmp(buff, "false") == 0) {
				pushToken(&result, BOOLEAN_VALUE);
				result.tokens[result.size - 1].value = buff;
			}
			else if(strcmp(buff, "null") == 0) {
				pushToken(&result, NU);
			}
			else if(strcmp(buff, "use") == 0) {
				pushToken(&result, USE);
			}
			else if(strcmp(buff, "var") == 0) {
				pushToken(&result, VAR);
			}
			else {
				pushToken(&result, KEYWORD);
				result.tokens[result.size - 1].value = buff;
			}
		}
		else {
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
				case '?': pushToken(&result, NONE); break;
				
				case '+':
				case '-':
				case '*':
				case '/':
				case '^':
					pushToken(&result, MATH_OP);
					result.tokens[result.size - 1].value[0] = c;
			}
		}
	}

	return result;
}


