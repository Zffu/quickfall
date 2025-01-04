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

/**
 * Parses a AST function into IR.
 * @param node the AST node representing the function.
 */
IR_FUNCTION parseFunction(AST_FUNCTION_DEC* node) {
    IR_FUNCTION func = {0};
    func.blocks = malloc(sizeof(IR_BASIC_BLOCK*));
    func.blockCount++;

    func.funcName = node->funcName;

    func.blocks[0] = malloc(sizeof(IR_BASIC_BLOCK));

    func.blocks[0]->instructions = NULL;
    func.blocks[0]->instructionCount = 0;

    //todo: move this to another function when finished
    while(node->body != NULL) {
        AST_TREE_BRANCH* b = (AST_TREE_BRANCH*) node->body;

        switch(b->type) {
            case AST_TYPE_VARIABLE_DECLARATION:
                parseVariableDeclaration(func.blocks[0], (AST_VARIABLE_DEC*)b);
                
                break;

        }

        node->body = b->next;
    }

    return func;
}

/**
 * Parses a AST Asm function into IR.
 * @param node the AST node representing the Asm function.
 */
IR_FUNCTION parseASMFunction(AST_ASM_FUNCTION_DEC* node) {
    IR_FUNCTION func = {0};
    func.blocks = malloc(sizeof(IR_BASIC_BLOCK*));

    func.blocks[0] = malloc(sizeof(IR_BASIC_BLOCK));
    func.blocks[0]->instructions = NULL;
    func.blocks[0]->instructionCount = 0;

    parseQAsmInstructions(func, node->buff, node->buffIndex);

    return func;
}