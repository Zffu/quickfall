/**
 * IR for variable related.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../parser/structs/variables.h"

#include "./values.h"

#include "../ir.h"

/**
 * Parses a variable declaration.
 * @param block the IR basic block to append to.
 * @param node the AST node representing the variable.
 */
void parseVariableDeclaration(IR_BASIC_BLOCK* block, AST_VARIABLE_DEC* node) {
    int allocSize = 0;
    if(node->type[0] == 0x01) allocSize = 32; // int32

    int paramsSize = 4 + strlen(node->name);

    unsigned char* params = malloc(paramsSize - 1);

    char* name = node->name;

    params[0] = (allocSize >> 24) & 0xFF;
    params[1] = (allocSize >> 16) & 0xFF;
    params[2] = (allocSize >> 8) & 0xFF;
    params[3] = allocSize & 0xFF;

    int i = 4;
    char c;

    while(c = *node->name++) {
        params[i] = c;

        if(c == '\0') break;
        ++i;
    }

    appendInstruction(block, S_ALLOC, params, paramsSize);

    if(node->value != NULL) {
        paramsSize = strlen(name) + getValueSize(node->type[0]);
        params = malloc(paramsSize);
        
        i = 0;
        while(c = *name++) {
            params[i] = c;

            if(c == '\0') break;
            ++i;
        }

        parseValue(params, i, node->value);

        appendInstruction(block, PTR_SET, params, paramsSize);
    }
}

/**
 * Parses a variable modification.
 * @param block the IR basic block to append to.
 * @param node the AST node representing the variable.
 */
inline void parseVariableModification(IR_BASIC_BLOCK* block, AST_VARIABLE_MOD* node) {
    int paramsSize = strlen(node->name) + getValueSize(0x01); // int32 for now, todo: change to hashmap stored type byte
    unsigned char* params = malloc(paramsSize);

    int i = 0;
    char c;

    while(c == *node->name++) {
        params[i] = c;
        ++i;
    }

    parseValue(params, i, node->value);
    appendInstruction(block, PTR_SET, params, paramsSize);
}