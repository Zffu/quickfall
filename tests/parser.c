/**
 * A simple parser AST test.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/lexer/lexer.h"

#include "../src/parser/parser.h"
#include "../src/parser/ast.h"

void dumpASTTree(AST_NODE* node, int depth);

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Usage: <exec> <file>\n");
		return -1;
	}

	FILE* fptr = fopen(argv[1], "r");

	if(fptr == NULL) {
		printf("Couldn't open file!\n");
		return -1;
	}

	fseek(fptr, 0, SEEK_END);
	int size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	char* buff = malloc(size + 1);

	fread(buff, 1, size, fptr);
	buff[size] = '\0';
	fclose(fptr);

	struct LexerResult result = runLexer(buff);
	struct ASTNode* root = parseNodes(result, 0, AST_ROOT);
}

void dumpASTTree(AST_NODE* root, int depth) {
	if(root->left != NULL) dumpASTTree(root->left, depth + 1);
	if(root->right != NULL) dumpASTTree(root->right, depth + 1);
	if(root->next != NULL) dumpASTTree(root->next, depth);

	printf("AST t: %d, v: %s\n", root->type, root->value);
}
