/**
 * Function-related AST parsing.
 */

#include <stdint.h>
#include <stdlib.h>

#include "./variables.h"

#include "../parser.h"
#include "../ast.h"

#include "../../lexer/tokens.h"
#include "../../lexer/lexer.h"

#include "../../utils/logging.c"

/**
 * Parse the parameters from a function definition (for example).
 * @param result the lexer result.
 * @param index the starting index of the parsing.
 */
AST_NODE* parseParameters(LEXER_RESULT result, int index) {

	AST_NODE* root = createASTNode(AST_PARAMETER);
	AST_NODE* current = root;

	int stack = 0;	

	for(; index < result.size + 1; ++index) {
		TOKEN t = result.tokens[index];

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

				TOKEN next = result.tokens[index + 1];

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
				root->endingIndex = index;
				return root;
			case PAREN_OPEN:
				continue;
			default:
				printf("Type: %d", t.type);
				return NULL;

		}
	}
}

/**
 * Parses the arguments passed during a function call (for example).
 * @param result the result of the lexer.
 * @param index the starting index of the parsing.
 */
AST_NODE* parseArguments(LEXER_RESULT result, int index) {
	AST_NODE* root = NULL;
	AST_NODE* current = root;

	for(; index < result.size + 1; ++index) {
		TOKEN t = result.tokens[index];

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

AST_NODE* parseFunctionDeclaration(LEXER_RESULT result, int index) {

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

	node->right = parseNodes(result, params->endingIndex, AST_FUNCTION_ROOT);

	node->endingIndex = node->right->endingIndex;

	return node;
}

AST_NODE* parseASMFunctionDeclaration(LEXER_RESULT result, int index) {
	AST_NODE* node = createASTNode(AST_ASM_FUNCTION_DECLARATION);
	
	node->left = createASTNode(AST_FUNCTION_HEADER);

	if(result.tokens[index + 1].type != KEYWORD) {
		return NULL;
	}

	node->left->right = createASTNode(AST_VARIABLE_NAME);
	node->left->right->value = result.tokens[index + 1].value;

	AST_NODE* params = parseParameters(result, index + 2);

	if(params == NULL) {
		return NULL;
	}

	node->left->left = params;

	index = params->endingIndex + 2;

	int buffSize = 32;
	int buffIndex = 0;
	uint8_t* buff = malloc(sizeof(uint8_t) * buffSize);

	for(; index <= result.size; ++index) {
		TOKEN t = result.tokens[index];

		if(t.type == BRACKETS_CLOSE) {
			break;
		}

		if(t.type != NUMBER) {
			return NULL;
		}

		buff[buffIndex] = strtol(t.value, NULL, 16);
		buffIndex++;
	}

	node->endingIndex = index;

	buff = realloc(buff, sizeof(uint8_t) * buffIndex);
	
	node->valueSize = buffIndex;
	node->value = buff;

	return node;
}

AST_NODE* parseFunctionInvoke(LEXER_RESULT result, int index) {
	AST_NODE* node = createASTNode(AST_FUNCTION_INVOKE);

	node->value = result.tokens[index].value;
	
	AST_NODE* args = parseArguments(result, index + 2);

	node->endingIndex = index;

	if(args != NULL) {
		node->right = args;
		node->endingIndex = args->endingIndex;
	}

	return node;
}
