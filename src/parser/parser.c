/**
 * The parser of Quickfall.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../lexer/lexer.h"
#include "../lexer/tokens.h"

/**
 * A node of the parser, allows for a tree-ish visualization of the parser sub groups.
 */
struct ParserNode {
    struct ParserNode* children;
    struct Token* tokens;
    int index;
};

/**
 * <p>Runs the parser of the provided LexerResult.
 */
void runParser(struct LexerResult result) {
    struct ParserNode root;
    
    struct ParserNode* branch = &root;
    struct ParserNode* latest = &root;

    for(int i = 0; i < result.size; ++i) {
        struct Token token = result.tokens[i];

        if(token.type == PAREN_OPEN || token.type == BRACKETS_OPEN || token.type == ARRAY_OPEN) {
            if(latest->children == NULL) {
                latest->children = malloc(result.size - 2 * sizeof(struct Token)); //todo: optimise this
            }
            
            latest->index++;
            branch = latest;
            latest = &latest->children[latest->index];
        }

        if(token.type == PAREN_CLOSE || token.type == BRACKETS_CLOSE || token.type == ARRAY_CLOSE) {
            if(branch != NULL) {
                latest = branch;
            }
        }
    }

    printf("sjjduios");
}
