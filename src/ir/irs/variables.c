/**
 * IR for variable related.
 */

#include "../../parser/structs/variables.h"

#include "../ir.h"

/**
 * Parses a variable declaration.
 * @param block the IR basic block to append to.
 * @param node the AST node representing the variable.
 */
inline void parseVariableDeclaration(IR_BASIC_BLOCK block, AST_VARIABLE_DEC* node) {
    int allocSize = 0;

    if(node->type == 0x01) allocSize = 32; // int32
    
    int paramsSize = 4 + strlen(node->name);
    unsigned char* params = malloc(paramsSize);

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
}