/**
 * A simple parser AST test.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/lexer/lexer.h"

#include "../src/parser/parser.h"
#include "../src/parser/ast.h"

void dumpASTTree(AST_NODE* node, int depth);

int runParserTest(char* buff) {
	LEXER_RESULT result = runLexer(buff, strlen(buff));

	AST_NODE* root = parseNodes(result, 0, AST_ROOT);

	dumpASTTree(root, 0);
}

char* debug[12] = {"Root", "Type Node", "Variable Name", "Variable Value", "Variable Declaration", "Variable Reference", "Function Declaration", "Function Header", "Math Operator", "Math Operation", "Math Operation Header", "Parameter"};

void dumpASTTree(AST_NODE* node, int depth) {
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
