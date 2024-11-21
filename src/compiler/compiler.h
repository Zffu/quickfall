/**
 * The main compiler file of Quickfall.
 */

#ifndef COMPILER_H
#define COMPILER_H

#include "../parser/ast.h"

/**
 * The object that gets passed trough the compiling functions.
 */
struct CompilingContext {
    char* defaultSection; // the default (.LC0 in x64) section, is used to store variables for now.
    char* sections; // the additional sections generated.
    char* main; // the main function.
};

/**
 * Compiles the AST node tree into Assembly.
 */
char* compile(struct ASTNode* node, char* platform);

#endif