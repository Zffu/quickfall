/**
 * The main compiler file of Quickfall.
 */

#ifndef COMPILER_H
#define COMPILER_H

#include "../parser/ast.h"

struct CompilerOutput {
    char output[2048];
};

struct CompilerOutput compile(struct ASTNode* node);

#endif