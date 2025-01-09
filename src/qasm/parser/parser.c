/**
 * The parser of QuickAssembly. The inline assembly of Quickfall.
 */

#include <stdio.h>
#include <string.h>
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
void parseQAsmInstructions(IR_BASIC_BLOCK* block, char* buffer, int size) {
    char** buff = malloc(sizeof(char*) * 10);
    int buffIndex = 0;

    int secIndex = 0;

    // Creating the buffers.
    for(int i = 0; i < 10; ++i) {
        buff[i] = malloc(32);
    }

    for(int i = 0; i < size; ++i) {
        char c = buffer[i];

        if(c == '\0') return;

        if(c == '\n') {
            IR_INSTRUCTION* instruction = parseInstruction(buff, buffIndex);

            if(instruction == NULL) {
                printf("Error: Coudln't parse QuickAssembly instruction named %s!\n", buff[0]);
            }
            else {
                pushInstruction(block, instruction);
            }

            secIndex = 0;
            buffIndex = 0;
        }
        else if(c == ' ') {
            ((char*)buff[buffIndex])[secIndex] = '\0';
            secIndex = 0;
            buffIndex++;
        }
        else {
            ((char*)buff[buffIndex])[secIndex] = c;
            secIndex++;
        }
    }

    for(int i = 0; i < 10; ++i) {
        free(buff[i]);
    }

    free(buff);
}

/**
 * Parses a QuickAssembly instruction.
 */
IR_INSTRUCTION* parseInstruction(char** buff, int bufferSize) {
    IR_INSTRUCTION* instruction = malloc(sizeof(IR_INSTRUCTION));

    int instructionHash = hashstr(buff[0]);

    void** b;

    // Determines the instruction type based on the string hash.
    switch(instructionHash) {
        case 2985:
            instruction->opCode = BLOCK_SWAP;
            b = malloc(sizeof(void*));
            parseInt32(b, 0, buff[1]);

            instruction->params = b;
            instruction->paramCount = 1;
            break;
        case 2987:
            instruction->opCode = COND_BLOCK_SWAP;
            b = malloc(sizeof(void*) * 2);

            parseInt32(b, 0, buff[1]);
            parseVariableName(b, 1, buff[2]);

            instruction->params = b;
            instruction->paramCount = 2;
            break;
        case 3275:
            instruction->opCode = LOGICAL_BLOCK_SWAP;
            b = malloc(sizeof(int*) * 3);

            parseInt32(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);
            parseVariableName(b, 2, buff[3]);

            instruction->params = b;
            instruction->paramCount = 3;
            break;
        case 1798:
            instruction->opCode = S_ALLOC;
            b = malloc(sizeof(void*) * 2);

            parseInt32(b, 0, buff[1]);
            parseVariableName(b, 1, buff[2]);

            instruction->params = b;
            instruction->paramCount = 2;
            break;
        case 2887:
            instruction->opCode = PTR_SET;
            b = malloc(sizeof(void*) * 2);

            parseInt32(b, 0, buff[1]);
            parseVariableName(b, 1, buff[2]);

            instruction->params = b;
            instruction->paramCount = 2;
            break;
        case 2472:
            instruction->opCode = PTR_LOAD;
            b = malloc(sizeof(void*) * 2);

            parseVariableName(b, 0, buff[1]);
            parseVariableName(b, 1, buff[2]);

            instruction->params = b;
            instruction->paramCount = 2;
            break;
        case 452:
            instruction->opCode = IADD;
            b = malloc(sizeof(void*) * 3);

            parseVariableName(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);
            parseInt32(b, 2, buff[3]);

            instruction->params = b;
            instruction->paramCount = 3;
            break;
        case 1508:
            instruction->opCode = ISUB;
            b = malloc(sizeof(void*) * 3);

            parseVariableName(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);
            parseInt32(b, 2, buff[3]);

            instruction->params = b;
            instruction->paramCount = 3;
            break;
        case 1636:
            instruction->opCode = IMUL;
            b = malloc(sizeof(void*) * 3);

            parseVariableName(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);
            parseInt32(b, 2, buff[3]);

            instruction->params = b;
            instruction->paramCount = 3;
            break;
        case 1284:
            instruction->opCode = IDIV;
            b = malloc(sizeof(void*) * 3);

            parseVariableName(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);
            parseInt32(b, 2, buff[3]);

            instruction->params = b;
            instruction->paramCount = 3;
            break;
        case 1188:
            instruction->opCode = ICMP;
            b = malloc(sizeof(void*) * 3);

            parseVariableName(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);
            parseInt32(b, 2, buff[3]);

            instruction->params = b;
            instruction->paramCount = 3;
            break;
        case 1350:
            instruction->opCode = ICMP_H;
            b = malloc(sizeof(void*) * 3);

            parseVariableName(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);
            parseInt32(b, 2, buff[3]);

            instruction->params = b;
            instruction->paramCount = 3;
            break;
        case 1478:
            instruction->opCode = ICMP_L;
            b = malloc(sizeof(void*) * 3);

            parseVariableName(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);
            parseInt32(b, 2, buff[3]);

            instruction->params = b;
            instruction->paramCount = 3;
            break;
        case 3272:
            instruction->opCode = PRM_PUSH;
            b = malloc(sizeof(void*) * 2);

            parseVariableName(b, 0, buff[1]);
            parseInt32(b, 1, buff[2]);

            instruction->params = b;
            instruction->paramCount = 2;
            break;
        case 3144:
            instruction->opCode = RET_PUSH;
            b = malloc(sizeof(void*));

            parseVariableName(b, 0, buff[1]);

            instruction->params = b;
            instruction->paramCount = 1;
            break;
        case 772:
            instruction->opCode = CALL;
            b = malloc(sizeof(void*));

            parseVariableName(b, 0, buff[1]);
            
            instruction->params = b;
            instruction->paramCount = 1;
            break;
        case 1283:
            instruction->opCode = RET;
            instruction->params = NULL;
            instruction->paramCount = 0;
            break;
        default:
            printf("Error: Unknown instruction %s!\n", buff[0]);
            return NULL;
    }
}