/**
 * The Intermediate Representation of Quickfall Code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./instructions.h"
#include "./structs.h"

#include "../parser/structs/tree.h"
#include "../parser/structs/functions.h"
#include "../parser/structs/variables.h"
#include "../parser/structs/values.h"

#include "./irs/variables.h"
#include "./irs/values.h"

#include "../parser/ast.h"

/**
 * Appends an IR instruction into the basic block.
 * @param block the IR basic block.
 * @param instruction the instruction.
 */
void pushInstruction(IR_BASIC_BLOCK* block, IR_INSTRUCTION* instruction) {
    if(block->allocatedSize == 0) {
        block->instructions = malloc(sizeof(IR_INSTRUCTION*) * 20);
        block->allocatedSize = 20;    
    }

    block->instructions[block->instructionCount] = instruction;
    block->instructionCount++;
}


/**
 * Appends an IR instruction into the basic block.
 * @parma block the IR basic block.
 * @param opCode the operation code of the instruction.
 * @param params the parameters of the operation.
 * @param paramsCount the count of the parameters of the operation.
 */
void appendInstruction(IR_BASIC_BLOCK* block, IR_INSTRUCTION_CODE code, unsigned char params[], int paramsCount) {
    IR_INSTRUCTION* instruction = malloc(sizeof(IR_INSTRUCTION));

    instruction->opCode = code;
    instruction->params = params;
    instruction->paramCount = paramsCount;

    pushInstruction(block, instruction);
}

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