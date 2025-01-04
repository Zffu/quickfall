/**
 * IR for variable related.
 */

#include <stdlib.h>
#include <string.h>

#include "../../parser/structs/variables.h"

#include "./values.h"

#include "../ir.h"

/**
 * Parses a variable declaration.
 * @param block the IR basic block to append to.
 * @param node the AST node representing the variable.
 */
inline void parseVariableDeclaration(IR_BASIC_BLOCK* block, AST_VARIABLE_DEC* node) {
    int allocSize = 0;

    if(node->type[0] == 0x01) allocSize = 32; // int32
    
    int paramsSize = 4 + strlen(node->name);
    unsigned char* params = malloc(paramsSize);

    char* name = node->name;

    int i;
    char c;

    while(c = *node->name++) {
        params[i] = c;

        if(c == '\0') break;
        ++i;
    }

    params[i + 1] = (allocSize >> 24) & 0xFF;
    params[i + 2] = (allocSize >> 16) & 0xFF;
    params[i + 3] = (allocSize >> 8) & 0xFF;
    params[i + 4] = allocSize & 0xFF;

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