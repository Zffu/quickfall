/**
 * The compiler of Quickfall.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./compiler.h"
#include "./objects.h"
#include "../parser/ast.h"
#include "../utils/logging.c"

#include "./att/att-win.h"
#include "./att/att-linux.h"

#include "../utils/hashmap.h"
#include "../utils/hash.h"

/**
 * Assembly format defintions. Will be changed by the architure.
 */
char** ARGUMENT_REGISTRIES = NULL;
char** SECTION_TYPES = NULL;

/**
 * The maximum hash the hashmaps can store.
 */
#define MAX_HASH_CAPACITY 256000

struct Context parseContext(struct ASTNode* node) {
	struct Context ctx = {0};

	ctx.variables = malloc(sizeof(struct Variable*) * 50);
	ctx.functions = malloc(sizeof(struct Function*) * 50);

	ctx.variableHashMap = createHashmap(512, 500);
	ctx.functionHashMap = createHashmap(512, 500);

	ctx.variableCount = 0;
	ctx.functionCount = 0;

	
			
	return ctx;

}

/**
 * Compiles the context down to assembly.
 */
char* compileV2(struct Context context) {
	char* firstSection = malloc(1024);
	char* sections = malloc(1024);
	char* main = malloc(1024);

	firstSection[0] = '\0';
	sections[0] = '\0';
	main[0] = '\0';

	int sectionIndex = 0;
	int stackSize = 0;

	// Platform def
	ARGUMENT_REGISTRIES = ATTWIN_ARGUMENT_REGISTRIES;
	SECTION_TYPES = ATTWIN_SECTION_TYPES;

	strcat(firstSection, ".LC0:\n    .globl  main");

	for(int i = 0; i < context.variableCount; ++i) {
		if(context.variables[i]->type[0] == 's') {
			if(sectionIndex == 0) {
				strcat(firstSection, "\n    ");
				strcat(firstSection, SECTION_TYPES[0]);
				strcat(firstSection, "  ");
				strcat(firstSection, "\"");
				strcat(firstSection, context.variables[i]->value);
				strcat(firstSection, "\"");
			}
			else {
				strcat(sections, ".LC");

				char secI[5];
				snprintf(secI, 5, "%d", sectionIndex);

				strcat(sections, secI);
				strcat(sections, ":\n    ");
				strcat(sections, SECTION_TYPES[0]);
				strcat(sections, "  ");
				strcat(sections, "\"");
				strcat(sections, context.variables[i]->value);
				strcat(sections, "\"");
			}
			sectionIndex++;
		}
		else if(context.variables[i]->type[0] == 'n') {
			stackSize += 4;

			strcat(main, "\n    movq    $");
			strcat(main, context.variables[i]->value);
			strcat(main, ", -");

			char sI[5];
			snprintf(sI, 5, "%d", stackSize);

			strcat(main, sI);
			strcat(main, "(%rsp)");
		}
	}

	char* buff = malloc(1024);
	
	buff[0] = '\0';

	strcat(buff, firstSection);
	strcat(buff, sections);
	strcat(buff, "\n\nmain:");

	char size[5];
	snprintf(size, 5, "%d", stackSize);

	if(stackSize > 0) {
		strcat(buff, "\n    subq    $");
		strcat(buff, size);
		strcat(buff, ", %rsp");
	}

	strcat(buff, main);

	if(stackSize > 0) {
		strcat(buff, "\n    addq    $");
		strcat(buff, size);
		strcat(buff, ", %rsp");
	}

	return buff;
}
