/**
 * The code in charge of managing the standart library usage in Quickfall.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./compiler.h"
#include "./platforms/windowsx86-64.h"

#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../parser/ast.h"

/**
 * Loads a component (a file) of the standart library and dump its contents into the assembly output.
 * @param ctx the compiling context of the currently running compile attempt.
 * @param component the component name (file name) of the part to load.
 */
void loadAndDump(struct CompilingContext ctx, char* component) {
	char fileName[32] = "stdl/";
	strcat(fileName, component);
	strcat(fileName, ".qfall");

	FILE* fptr = fopen(fileName, "r");

	if(fptr == NULL) {
		printf("Error: Could not find STDL component named %s!", component);
		return;
	}

	fseek(fptr, 0, SEEK_END);
	int size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	char* buff = malloc(size + 1);
	buff[size] = '\0';

	fread(buff, 1, size, fptr);
	fclose(fptr);

	struct LexerResult result = runLexer(buff);
	struct ASTNode* node = runParser(result);

	win64(ctx, node, 0); // todo: change this according to the platform selected
}
