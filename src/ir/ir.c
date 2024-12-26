/**
 * The Intermediate Representation of Quickfall Code.
 */

#include <stdlib.h>
#include <string.h>

#include "./instructions.h"
#include "./structs.h"

#include "../../parser/ast.h"

/**
 * Appends an IR instruction into the basic block.
 * @parma block the IR basic block.
 * @param opCode the operation code of the instruction.
 * @param params the parameters of the operation.
 * @param paramsCount the count of the parameters of the operation.
 */
void appendInstruction(IR_BASIC_BLOCK block, IR_INSTRUCTION_CODE code, unsigned char params[], int paramsCount) {
    IR_INSTRUCTION instruction = {0};

    instruction.opCode = code;
    instruction.params = params;
    instruction.paramCount = paramsCount;


    if(block.instructions == NULL) {
        block.instructions = malloc(sizeof(IR_INSTRUCTION) * 20);
        block.allocatedSize = 20;
    }

    block.instructions[block.instructionCount] = instruction;
    block.instructionCount++;
}

/**
 * Parses a AST function into IR.
 * @param node the AST node representing the function.
 */
IR_FUNCTION parseFunction(AST_NODE* node) {
    IR_FUNCTION func = {0};
    func.blocks = malloc(sizeof(IR_BASIC_BLOCK));
    func.blockCount++;

    func.blocks[0].instructions = NULL;
    func.blocks[0].instructionCount = 0;

    while(node != NULL) {

        switch(node->type) {
            case AST_VARIABLE_DECLARATION:
                // For now let's just say that every variable is 32 bits.
                //todo: change this when typing gets added.

                int size = strlen(node->left->value) + sizeof(int);

                unsigned char* ptr = malloc(size);

                int i = 0;
                char c;

                while(c = *node->left->value++) {
                    ptr[i] = c;
                    ++i;

                    if(c == '\0') break;
                }

                ptr[i] = (32 >> 24) & 0xFF;
                ptr[i + 1] = (32 >> 16) & 0xFF;
                ptr[i + 2] = (32 >> 8) & 0xFF;
                ptr[i + 3] = 32 & 0xFF;

                appendInstruction(func.blocks[0], S_ALLOC, ptr, size);
                
                ptr = malloc(sizeof(int));
                ((int*)ptr)[0] = atoi(node->right->value);

                appendInstruction(func.blocks[0], PTR_SET, ptr, sizeof(int));
                break;
        }

        node = node->next;
    }

    return func;
}