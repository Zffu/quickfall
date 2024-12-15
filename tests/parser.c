/**
 * A simple parser AST test.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/lexer/lexer.h"

#include "../src/parser/parser.h"
#include "../src/parser/ast.h"

void dumpASTTree(AST_NODE* node, int depth);

inline int runParserTest(char* buff) {
	struct LexerResult result = runLexer(buff);

	AST_NODE* root = parseNodes(buff, 0, AST_ROOT);

	dumpASTTree(node, 0);
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
