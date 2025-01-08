/**
 * IR for function related.
 */

#include <stdlib.h>

#include "../../qasm/parser/parser.h"

#include "../structs.h"

#include "../../parser/structs/functions.h"
#include "../../parser/structs/variables.h"
#include "../../parser/structs/tree.h"

#include "../../parser/ast.h"

#include "./variables.h"

#include "../../utils/hash.h"
#include "../../utils/hashmap.h"

/**
 * Parses a AST function into IR.
 * @param node the AST node representing the function.
 */
void parseFunction(IR_OUTPUT* out, AST_FUNCTION_DEC* node) {
    int hash = strhash(node->funcName);
    IR_FUNCTION* func = malloc(sizeof(IR_FUNCTION));

    func->startBlock = out->blockCount;
    func->typeCount = node->parameterIndex;

    func->types = malloc(func->typeCount + 1);

    if(node->returnType != NULL) func->types[0] = node->returnType[0];
    else func->types[0] == 0x00;

    for(int i = 0; i < func->typeCount; ++i) {
        func->types[i + 1] = node->parameters[i].type;
    }

    hashPut(out->map, hash, func);

    out->blocks[out->blockCount] = malloc(sizeof(IR_BASIC_BLOCK));
    out->blocks[out->blockCount]->instructions = NULL;
    out->blocks[out->blockCount]->instructionCount = 0;
    out->blocks[out->blockCount]->allocatedSize = 0;

    while(node->body != NULL) {
        AST_TREE_BRANCH* branch = (AST_TREE_BRANCH*) node->body;
        switch(branch->type) {
            case AST_TYPE_VARIABLE_DECLARATION:
                parseVariableDeclaration(out->blocks[out->blockCount], (AST_VARIABLE_DEC*)branch);
                break;
            case AST_TYPE_VARIABLE_MODIFICATION:
                parseVariableModification(out->blocks[out->blockCount], (AST_VARIABLE_MOD*)branch);
                break;
        }
        node->body = branch->next;
    }

}

/**
 * Parses a AST Asm function into IR.
 * @param node the AST node representing the Asm function.
 */
void parseASMFunction(IR_OUTPUT* out, AST_ASM_FUNCTION_DEC* node) {
    IR_FUNCTION* func = malloc(sizeof(IR_FUNCTION));
    func->startBlock = out->blockCount;

    func->types = malloc(1);
    func->types[0] = 0x00;
    func->typeCount = 1;
    
    hashPut(out->map, hashstr(node->funcName), func);

    out->blocks[out->blockCount] = malloc(sizeof(IR_BASIC_BLOCK));
    out->blocks[out->blockCount]->instructions = NULL;
    out->blocks[out->blockCount]->instructionCount = 0;

    parseQAsmInstructions(func, node->buff, node->buffIndex);
}