/**
 * Test to check if the IR is working correctly.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/lexer/lexer.h"
#include "../src/lexer/tokens.h"

#include "../src/parser/parser.h"
#include "../src/parser/ast.h"

#include "../src/compiler/compiler.h"
#include "../src/compiler/ir.h"

int main(int argc, char** argv) {

	if(argc < 2) {
		printf("Usage: <executable> <file>\n");
		return -1;
	}

	FILE* fptr = fopen(argv[1], "r");

	if(fptr == NULL) {
		return -1;
	}

	fseek(fptr, 0, SEEK_END);
	int size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	char* buff = malloc(size + 1);

	fread(buff, 1, size, fptr);
	buff[size] = '\0';

