/**
 * Function-related AST parsing.
 */

#include "./variables.h"

#include "../ast.h"
#include "../../utils/logging.h"

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
