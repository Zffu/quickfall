/**
 * The Intermediate Representation of Quickfall Code.
 */

#include <stdlib.h>
#include <string.h>

#include "./instructions.h"
#include "./structs.h"

#include "../../parser/structs/tree.h"
#include "../../parser/structs/functions.h"
#include "../../parser/structs/variables.h"
#include "../../parser/structs/values.h"

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
IR_FUNCTION parseFunction(AST_FUNCTION_DEC* node) {
    IR_FUNCTION func = {0};
    func.blocks = malloc(sizeof(IR_BASIC_BLOCK));
    func.blockCount++;

    func.funcName = node->funcName;

    func.blocks[0].instructions = NULL;
    func.blocks[0].instructionCount = 0;

    //todo: move this to another function when finished
    while(node->body != NULL) {
        AST_TREE_BRANCH* b = (AST_TREE_BRANCH*) node->body;

        switch(b->type) {
            case AST_TYPE_VARIABLE_DECLARATION:
                AST_VARIABLE_DEC* var = (AST_VARIABLE_DEC*) b;
                
                int size = 0;
                if(var->type == 0x01) size = 32; // int32

                int paramsSize = 4 * strlen(var->name);
                unsigned char* params = malloc(paramsSize);

                params[0] = (size >> 24) & 0xFF;
                params[1] = (size >> 16) & 0xFF;
                params[2] = (size >> 8) & 0xFF;
                params[3] = size & 0xFF;

                int i = 0;
                char c;

                while(c = *var->name++) {
                    params[4 + i] = c;

                    if(c == '\0') break;
                    ++i;
                }

                appendInstruction(func.blocks[0], S_ALLOC, params, paramsSize);

                if(var->value != NULL) {
                    if(((AST_TREE_BRANCH*)var->value)->type == AST_TYPE_VALUE) {
                        AST_VALUE* val = (AST_VALUE*)var->value;

                        if(val->valueType != var->type) {
                            printf("Error: the variable value doesn't match the variable type!\n");
                            return;
                        }

                        int size;

                        if(var->type == 0x01) { // i32
                            size = 4;
                            params = malloc(4);

                            int num = atoi(val->value);

                            params[0] = (num >> 24) & 0xFF;
                            params[1] = (num >> 16) & 0xFF;
                            params[2] = (num >> 8) & 0xFF;
                            params[3] = num & 0xFF;
                        }

                        appendInstruction(func.blocks[0], PTR_SET, params, size);
                    }
                }

                break;

        }

        node->body = b->next;
    }

    return func;
}