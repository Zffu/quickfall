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
#include "./irs/functions.h"

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
 * Converts the AST tree into IR.
 */
IR_OUTPUT* parseIR(AST_TREE_BRANCH* node) {
    IR_OUTPUT* out = malloc(sizeof(IR_OUTPUT));

    out->allocatedBlockCount = 0;
    out->blockCount = 0;
    out->blocks = NULL;
    out->map = malloc(sizeof(struct Hashmap));
    
    while(node != NULL) {
        switch(node->type) {
            case AST_TYPE_FUNCTION_DECLARATION:
                parseFunction(out, (AST_FUNCTION_DEC*)node);
                break;
            case AST_TYPE_ASM_FUNCTION_DECLARATION:
                parseASMFunction(out, (AST_ASM_FUNCTION_DEC*)node);
                break;
            case AST_TYPE_VARIABLE_DECLARATION:
                parseVariableDeclaration(out->blocks[0], (AST_VARIABLE_DEC*)node);
                break;
            case AST_TYPE_VARIABLE_MODIFICATION:
                parseVariableModification(out->blocks[0], (AST_VARIABLE_MOD*)node);
                break;
        }
        node = node->next;
    }

    return out;
}