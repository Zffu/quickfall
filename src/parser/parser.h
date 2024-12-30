/**
 * The Quickfall Parser & AST Generator.
 */

#include "./ast.h"
#include "./structs/tree.h"

#include "../lexer/lexer.h"

#ifndef PARSER_H
#define PARSER_H

/**
 * Parses the Lexer result into an AST root.
 * @param result the Lexer result.
 * @param startIndex the starting Index.
 * @param type the output AST type.
 */
void* parseRoot(LEXER_RESULT result, int startingIndex, AST_TYPE type);

/**
 * Appends a new node in the AST tree.
 * @param curr the current AST node.
 * @param root the root of the AST tree.
 * @param node the node to add to the tree.
 */
void append(AST_TREE_BRANCH* curr, AST_TREE_BRANCH* root, void* node);

#endif