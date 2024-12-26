/**
 * AST structure definitions for Tree related ASTs.
 */

#ifndef TREE_STRUCT_H
#define TREE_STRUCT_H

/**
 * The main AST root tree structure.
 */
typedef struct {
    unsigned char type; // The type of the AST node type (unused).

    void* next; // Refers to the next node in the tree.
    void* last; // Refers to the furthest / last node in the tree.

} AST_ROOT_TREE;


/**
 * The "base" type of each AST structure. Is used to cast to gather next branch.
 */
typedef struct {
    unsigned char type; // The type of the AST node type (unused.)
    void* next; // The next node in the tree.

} AST_TREE_BRANCH;

#endif