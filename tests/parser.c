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

	dumpASTTree(root, 0);
}

char* debug[12] = {"Root", "Type Node", "Variable Name", "Variable Value", "Variable Declaration", "Variable Reference", "Function Declaration", "Function Header", "Math Operator", "Math Operation", "Math Operation Header", "Parameter"};

void dumpASTTree(struct ASTNode* node, int depth) {
    for(int i = 0; i < depth; ++i) {
        printf("  ");
    }
    printf("AST Node of type (%d)\n", node->type);
    
    if(node->left != NULL) {
        dumpASTTree(node->left, depth + 1);
    }

    if(node->right != NULL) {
        dumpASTTree(node->right, depth + 1);
    }

    if(node->next != NULL) {
        dumpASTTree(node->next, depth);
    }
}
