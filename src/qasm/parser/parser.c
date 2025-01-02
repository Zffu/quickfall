/**
 * The parser of QuickAssembly. The inline assembly of Quickfall.
 */

#include <stdlib.h>

#include "./parser.h"

#include "./values.h"

#include "../../parser/structs/functions.h"

#include "../../ir/structs.h"
#include "../../ir/ir.h"
#include "../../ir/instructions.h"

#include "../../utils/hash.h"

/**
 * Parses QuickAssembly instructions.
 */
void parseQAsmInstructions(IR_FUNCTION func, char* buff, int size) {
    char** buff = malloc(sizeof(char*) * 10);
    int buffIndex = 0;

    int secIndex = 0;

    // Creating the buffers.
    for(int i = 0; i < 10; ++i) {
        buff[i] = malloc(32);
    }

    for(int i = 0; i < size; ++i) {
        char c = buff[i];

        if(c == '\0') return;

        if(c == '\n') {
            IR_INSTRUCTION* instruction = parseInstruction(buff, buffIndex);

            if(instruction != NULL) {
                printf("Error: Coudln't parse QuickAssembly instruction named %s!\n", buff[0]);
            }
            else {
                pushInstruction(func.blocks[0], *instruction); //todo: change ptr->obj to ptr
            }

            secIndex = 0;
            buffIndex = 0;
        }
        else if(c == ' ') {
            ((char*)buff[buffIndex])[secIndex] = '\0';
            buffIndex++;
        }
        else {
            ((char*)buff[buffIndex])[secIndex] = c;
            secIndex++;
        }
    }
}

/**
 * Parses a QuickAssembly instruction.
 */
inline IR_INSTRUCTION* parseInstruction(char** buff, int size) {
    IR_INSTRUCTION* instruction = malloc(sizeof(IR_INSTRUCTION));

    int instructionHash = hashstr(buff[0]);

    unsigned char* buff;

    // Determines the instruction type based on the string hash.
    switch(instructionHash) {
        case 2985:
            instruction->opCode = BLOCK_SWAP;
            buff = malloc(4);
            parseInt32(buff, 0, buff[1]);

            instruction->params = buff;
            instruction->paramCount = 4;
            break;
        case 2987:
            instruction->opCode = COND_BLOCK_SWAP;
            int size = 4 + strlen(buff[2]) - 1;
            buff = malloc(size);
            parseInt32(buff, 0, buff[1]);
            parseVariableName(buff, 5, buff[2]);

            instruction->params = buff;
            instruction->paramCount = size;
            break;
        case 3275:
            instruction->opCode = LOGICAL_BLOCK_SWAP;
            break;
        case 1798:
            instruction->opCode = S_ALLOC;
            break;
        case 2887:
            instruction->opCode = PTR_SET;
            break;
        case 2472:
            instruction->opCode = PTR_LOAD;
            break;
        case 452:
            instruction->opCode = IADD;
            break;
        case 1508:
            instruction->opCode = ISUB;
            break;
        case 1636:
            instruction->opCode = IMUL;
            break;
        case 1284:
            instruction->opCode = IDIV;
            break;
        case 1188:
            instruction->opCode = ICMP;
            break;
        case 1350:
            instruction->opCode = ICMP_H;
            break;
        case 1478:
            instruction->opCode = ICMP_L;
            break;
        case 3272:
            instruction->opCode = PRM_PUSH;
            break;
        case 3144:
            instruction->opCode = RET_PUSH;
            break;
        case 772:
            instruction->opCode = CALL;
            break;
        case 1283:
            instruction->opCode = RET;
            break;
        default:
            printf("Error: Unknown instruction %s!\n", buff[0]);
            return NULL;
    }
}