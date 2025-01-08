/**
 * The Quickfall Parser & AST Generator.
 */

#include <stdio.h>

#include "./parser.h"

#include "./ast.h"

#include "../lexer/lexer.h"

#include "./structs/tree.h"
#include "./structs/variables.h"

#include "./asts/variables.h"
#include "./asts/functions.h"


/**
 * Parses the Lexer result into an AST root.
 * @param result the Lexer result.
 * @param startingIndex the starting Index.
 * @param type the output AST type.
 */
void* parseRoot(LEXER_RESULT result, int startingIndex, AST_TYPE type) {
    AST_TREE_BRANCH* root = NULL;
    AST_TREE_BRANCH* curr = NULL;

    for(int i = startingIndex; i < result.size; ++i) {
        TOKEN t = result.tokens[i];

        switch(t.type) {
            case VAR:
                void* node = parseVariableDeclaration(result, i);
                append(curr, root, node);
                break;
            case KEYWORD:
                if(result.tokens[i + 1].type == KEYWORD) {
                    void* node = parseVariableDeclaration(result, i);
                    append(curr, root, node);
                    break;
                }
                
                if(result.tokens[i + 1].type == DECLARE) {
                    void* node = parseVariableModification(result, i);
                    append(curr, root, node);
                    break;
                }
            case FUNCTION:
                node = parseFunctionDeclaration(result, i);
                append(curr, root, node);
                break;
            
            case ASM_FUNCTION:
                node = parseASMFunctionDeclaration(result, i);
                append(curr, root, node);
                break;
 
            case BRACKETS_CLOSE:
                if(type == AST_TYPE_FUNC_ROOT) return root;
                break;

            default:
                printf("Error: Unexcepted token %d!\n", t.type);
                break;
        }
    }

    return root;
}

/**
 * Appends a new node in the AST tree.
 * @param curr the current AST node.
 * @param root the root of the AST tree.
 * @param node the node to add to the tree.
 */
void append(AST_TREE_BRANCH* curr, AST_TREE_BRANCH* root, void* node) {
    if(node == NULL) return;

    if(curr == NULL) {
        root = node;
        curr = root;
    }
    else {
        curr->next = node;
        curr = node;
    }
}