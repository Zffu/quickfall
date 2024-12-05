/**
 * Variable-related AST parsing.
 */

#include "../../lexer/lexer.h"
#include "../../lexer/tokens.h"

#include "../ast.h"

AST_NODE* parseVariableValue(struct LexerResult result, int index) {
	struct Token t = result.tokens[index];

	if(t.type == NUMBER || t.type == STRING || t.type == BOOLEAN_VALUE) {
		AST_NODE* node = createASTNode(AST_VARIABLE_VALUE);
		node->left = createASTNode(AST_TYPE);

		switch(t.type) {
			case NUMBER:
				node->left->value = "n";
				break;
			case STRING:
				node->left->value = "s";
				break;
			default:
				node->left->value = "b";
		
		}

		node->value = t.value;
		return node;
	}

	if(t.type == KEYWORD) {
		AST_NODE* node = createASTNode(AST_VARIABLE_REFERENCE);
		node->value = t.value;

		return node;
	}
}
