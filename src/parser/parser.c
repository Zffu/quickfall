/**
 * The parser of Quickfall.
 */

#include <stdio.h>

#include "../lexer/tokens.h"
#include "../lexer/lexer.h"

#include "./ast.h"

#include "./asts/variables.h"
#include "./asts/functions.h"

/**
 * Parses the lexer tokens into nodes starting from the index.
 * @param result the LexerResult provided by the lexer.
 * @param index the starting index.
 */
AST_NODE* parseNodes(struct LexerResult result, int index, enum ASTNodeType type) {
	AST_NODE* root = createASTNode(type);
	AST_NODE* current = root;

	for(; index <= result.size; ++index) {
		struct Token t = result.tokens[index];

		AST_NODE* node = NULL;

		switch(t.type) {
			case FUNCTION:
				node = parseFunctionDeclaration(result, index);
				if(node != NULL) {
					current->next = node;
					current = node;
					index = node->endingIndex;
				}

				break;
			case VAR:
				node = parseVariableDeclaration(result, index);
				if(node != NULL) {
					current->next = node;
					current = node;
					index = node->endingIndex;
				}
				break;
			case ASM_FUNCTION:
				node = parseASMFunctionDeclaration(result, index);
				if(node != NULL) {
					current->next = node;
					current = node;
					index = node->endingIndex;
				}
				break;

		}
	}

	return root;
}
