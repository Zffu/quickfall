/**
 * Math ASTs for the Quickfall parser.
 */

#include <stdlib.h>

#include "../../lexer/lexer.h"

#include "../ast.h"
#include "./variables.h"

/**
 * Parses the mathematical operation.
 * @param result the lexer result.
 * @param index the starting index.
 */
AST_NODE* parseMathematicalOpNode(struct LexerResult result, int index) {
	AST_NODE* node = createASTNode(AST_MATH_OPERATION);
	node->left = createASTNode(AST_MATH_OP_HEADER);

	node->left->left = createASTNode(AST_VARIABLE_NAME);
	node->left->left->value = result.tokens[index].value;

	node->left->right = createASTNode(AST_MATH_OPERATOR);

	node->left->right->value = malloc(2);
	node->left->right->value[0] = result.tokens[index + 1].value[0];
	node->left->right->value[1] = '\0';

	node->value = malloc(1);

	if(result.size >= index + 2 && result.tokens[index + 2].type == DECLARE) {
		node->value[0] = '1';
	}

	node->right = parseVariableValue(result, index + 2);
	node->endingIndex = node->right->endingIndex;

	return node;
}
