/**
 * Function-related AST parsing.
 */

#include "./variables.h"

#include "../parser.h"
#include "../ast.h"

#include "../../lexer/lexer.h"

/**
 * Parse the parameters from a function definition (for example).
 * @param result the lexer result.
 * @param index the starting index of the parsing.
 */
AST_NODE* parseParameters(struct LexerResult result, int index) {

	AST_NODE* root = createASTNode(AST_PARAMETER);
	AST_NODE* current = root;

	int stack = 0;	

	for(; index < result.size + 1; ++index) {
		struct Token t = result.tokens[index];

		switch(t.type) {
			case COMMA:
				if(stack == 0) {
					return NULL;
				}

				stack = 0;
				current->next = createASTNode(AST_PARAMETER);
				current = current->next;
				break;
			case NONE:
			case KEYWORD:
				if(stack == 2) {
					return NULL;
				}

				struct Token next = result.tokens[index + 1];

				if(next.type == NONE || next.type == KEYWORD) {
					current->left = createASTNode(AST_TYPE);
					current->left->value = next.value;
				}
				else {
					current->right = createASTNode(AST_VARIABLE_NAME);
					current->right->value = t.value;
				}

				stack++;
				break;
			case PAREN_CLOSE:
				if(stack != 0) {
					root->endingIndex = index;
					return root;
				}
				return NULL;
			default:
				return NULL;

		}
	}
}

/**
 * Parses the arguments passed during a function call (for example).
 * @param result the result of the lexer.
 * @param index the starting index of the parsing.
 */
AST_NODE* parseArguments(struct LexerResult result, int index) {
	AST_NODE* root = NULL;
	AST_NODE* current = root;

	for(; index < result.size + 1; ++index) {
		struct Token t = result.tokens[index];

		if(t.type == PAREN_CLOSE) {
			return root;
		}

		AST_NODE* arg = parseVariableValue(result, index);
		
		if(arg == NULL) return NULL;

		index = arg->endingIndex;

		if(root == NULL) {
			root = arg;
			current = root;
		}
		else {
			current->next = arg;	
		}
	}

	return NULL;
}

AST_NODE* parseFunctionDeclaration(struct LexerResult result, int index) {

	AST_NODE* node = createASTNode(AST_FUNCTION_DECLARATION);
	node->left = createASTNode(AST_FUNCTION_HEADER);

	if(result.tokens[index].type != KEYWORD) {
		return NULL;
	}

	int off = 1;

	switch(result.tokens[index + 1].type) {
		case KEYWORD:
			node->left->value = result.tokens[index].value;
			node->left->right = createASTNode(AST_VARIABLE_NAME);
			node->left->right->value = result.tokens[index + 1].value;
			++off;
			break;
		case PAREN_OPEN:
			node->left->value = "void";
			node->left->right = createASTNode(AST_VARIABLE_NAME);
			node->left->right->value = result.tokens[index].value;
			break;
		default:
			return NULL;
	}

	AST_NODE* params = parseParameters(result, index + off);

	if(params == NULL) return NULL;

	node->left->left = params;

	node->right = parseNodes(result, params->endingIndex);

	return node;
}
