/**
 * The file of the Quickfall CLI.
 * A modern, fast and lightweight programming language.
 * Usage:
 * quickfall build <input> -o <output> - Builds the input files into an output.
 * quickfall help - Shows the help command.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../parser/ast.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../compiler/compiler.h"

#include "../utils/logging.c"

// Version
#define VERSION "0.1.0"


void showCommandEntry(char* commandName, char* description, int argumentCount, char* argumentNames[], char* argumentDescriptions[]) {
	printf("\n    >  %s\n\n       %s%sDescription%s: %s\n", commandName, STYLE_BOLD, STYLE_UNDERLINE, RESET, description);

	if(argumentCount > 0) {
		printf("\n\n       %s%sArguments%s: ", STYLE_BOLD, STYLE_UNDERLINE, RESET);
		for(int i = 0; i < argumentCount; ++i) {
			printf("\n         > %s%s%s: %s", TEXT_GRAY, argumentNames[i], RESET, argumentDescriptions[i]);
		}
		printf("\n");
	}
}

void showHelpMessage() {
	printf("\n%sQuickfall%s - The programming language.\n\nCommands:\n", TEXT_CYAN, RESET);
	
	char** arguments = malloc(5 * 24);
	char** argumentDescriptions = malloc(5 * 256);
	
	arguments[0] = "-p";
	argumentDescriptions[0] = "Determines the targeted platform. Defaults to the current platform.";
	
	arguments[1] = "-o";
	argumentDescriptions[1] = "Determines the output file of the compiling. Is required";

	showCommandEntry("compile, c", "Compiles the Quickfall program into an executable for the targeted platform.", 2, arguments, argumentDescriptions);
	
	showCommandEntry("version, v", "Shows the current version of Quickfall.", 0, NULL, NULL);

	showCommandEntry("help, h", "Shows a message with helpful Quickfall information.", 0, NULL, NULL);

}


int main(int argc, char* argv[]) {
	if(argc < 2) {
		showHelpMessage();
		return -1;
	}

	switch(argv[1][0]) {
		case 'c':
			if(strlen(argv[1]) > 1 && strcmp(argv[1], "compile") != 0) {
				printf("Unknown command!\n");
				showHelpMessage();
				break;
			}
					
			printf("Compiling...");
			break;
		case 'v':
			if(strlen(argv[1]) > 1 && strcmp(argv[1], "version") != 0) {
				printf("Unknown command!\n");
				showHelpMessage();
				break;
			}
			printf("Quickfall ver");
			break;
		case 'h':
			if(strlen(argv[1]) > 1 && strcmp(argv[1], "help") != 0) {
				printf("Unknown command!\n");
				showHelpMessage();
				break;
			}
			showHelpMessage();
			break;
		default:
			printf("Unknown command!\n");
			showHelpMessage();
	}

}


