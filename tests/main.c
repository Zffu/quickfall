/**
 * Quickfall's Testing suite.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "./lexer.h"
#include "./parser.h"

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("Usage: <executable> <file> <tests...>\0");
		return -1;
	}

	FILE* fptr = fopen(argv[1], "r");
	
	fseek(fptr, 0, SEEK_END);
	int size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	char* buff = malloc(size + 1);

	fread(buff, 1, size, fptr);
	fclose(fptr);

	buff[size] = '\0';

	for(int i = 2; i < argv; ++i) {
		char* testName = argv[i];

		int code = 0;

		if(strcmp(testName, "lexer") == 0) {
			code = runLexerTest(buff);
		}
		if(strcmp(testName, "parser") == 0) {
			code = runParserTest(buff);
		}
		else if(strcmp(testName, "ir") == 0) {
			
		}

		if(code != -1) {
			printf("[OK] %s Test\n", testName);
		}
		else {
			printf("[FAILED] %s Test\n", testName);
		}
	}

}
