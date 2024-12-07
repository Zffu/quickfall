/**
 * The parser of Quickfall.
 */

#include "../lexer/lexer.h"
#include "./ast.h"

#include "./asts/functions.h"

/**
 * Parses the lexer tokens into nodes starting from the index.
 * @param result the LexerResult provided by the lexer.
 * @param index the starting index.
 */
AST_NODE* parseNodes(struct LexerResult result, int index, enum ASTNodeType type) {
	AST_NODE* root = createASTNode(type);
	AST_NODE* current = root;

	for(; index <= result.size; ++i) {
		struct Token t = result.tokens[index];

		switch(t.type) {
			case FUNC:
				AST_NODE* node = parseFunctionDeclaration(result, index);
				if(node != null) {
					current->next = node;
					current = node;
					index = node->endingIndex;
				}

				break;
				
		}
	}

	return root;
}
