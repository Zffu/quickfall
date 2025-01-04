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
void parseQAsmInstructions(IR_FUNCTION* func, char* buffer, int size) {
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
                pushInstruction(func->blocks[0], instruction);
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
}

/**
 * Parses a QuickAssembly instruction.
 */
IR_INSTRUCTION* parseInstruction(char** buff, int bufferSize) {
    IR_INSTRUCTION* instruction = malloc(sizeof(IR_INSTRUCTION));

    int instructionHash = hashstr(buff[0]);

    unsigned char* b;

    // Determines the instruction type based on the string hash.
    switch(instructionHash) {
        case 2985:
            instruction->opCode = BLOCK_SWAP;
            b = malloc(4);
            parseInt32(b, 0, buff[1]);

            instruction->params = b;
            instruction->paramCount = 4;
            break;
        case 2987:
            instruction->opCode = COND_BLOCK_SWAP;
            int size = 4 + strlen(buff[2]) - 1;
            b = malloc(size);
            parseInt32(b, 0, buff[1]);
            parseVariableName(b, 5, buff[2]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 3275:
            instruction->opCode = LOGICAL_BLOCK_SWAP;
            size = 8 + strlen(buff[3]) - 1;
            b = malloc(size);
            parseInt32(b, 0, buff[1]);
            parseInt32(b, 5, buff[2]);
            parseVariableName(b, 10, buff[3]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 1798:
            instruction->opCode = S_ALLOC;
            size = 4 + strlen(buff[2]) - 1;
            b = malloc(size);
            parseInt32(b, 0, buff[1]);
            parseVariableName(b, 5, buff[2]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 2887:
            instruction->opCode = PTR_SET;
            size = 4 + strlen(buff[2]) - 1;
            b = malloc(size);
            parseInt32(b, 0, buff[1]);
            parseVariableName(b, 5, buff[2]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 2472:
            instruction->opCode = PTR_LOAD;
            size = strlen(buff[1]) + strlen(buff[2]) - 2;
            b = malloc(size);
            int i = parseVariableName(b, 0, buff[1]);
            parseVariableName(b, i + 1, buff[2]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 452:
            instruction->opCode = IADD;
            size = strlen(buff[1]) + 7;
            b = malloc(size);
            i = parseVariableName(b, 0, buff[1]);
            parseInt32(b, i + 1, buff[2]);
            parseInt32(b, i + 6, buff[3]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 1508:
            instruction->opCode = ISUB;
            size = strlen(buff[1]) + 7;
            b = malloc(size);
            i = parseVariableName(b, 0, buff[1]);
            parseInt32(b, i + 1, buff[2]);
            parseInt32(b, i + 6, buff[3]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 1636:
            instruction->opCode = IMUL;
            size = strlen(buff[1]) + 7;
            b = malloc(size);
            i = parseVariableName(b, 0, buff[1]);
            parseInt32(b, i + 1, buff[2]);
            parseInt32(b, i + 6, buff[3]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 1284:
            instruction->opCode = IDIV;
            size = strlen(buff[1]) + 7;
            b = malloc(size);
            i = parseVariableName(b, 0, buff[1]);
            parseInt32(b, i + 1, buff[2]);
            parseInt32(b, i + 6, buff[3]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 1188:
            instruction->opCode = ICMP;
            size = strlen(buff[1]) + 7;
            b = malloc(size);
            i = parseVariableName(b, 0, buff[1]);
            parseInt32(b, i + 1, buff[2]);
            parseInt32(b, i + 6, buff[3]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 1350:
            instruction->opCode = ICMP_H;
            size = strlen(buff[1]) + 7;
            b = malloc(size);
            i = parseVariableName(b, 0, buff[1]);
            parseInt32(b, i + 1, buff[2]);
            parseInt32(b, i + 6, buff[3]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 1478:
            instruction->opCode = ICMP_L;
            size = strlen(buff[1]) + 7;
            b = malloc(size);
            i = parseVariableName(b, 0, buff[1]);
            parseInt32(b, i + 1, buff[2]);
            parseInt32(b, i + 6, buff[3]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 3272:
            instruction->opCode = PRM_PUSH;
            size = strlen(buff[1]) + 3;
            b = malloc(size);
            i = parseVariableName(b, 0, buff[1]);
            parseInt32(b, i + 1, buff[2]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 3144:
            instruction->opCode = RET_PUSH;
            size = strlen(buff[1]) - 1;
            b = malloc(size);
            parseVariableName(b, 0, buff[1]);

            instruction->params = b;
            instruction->paramCount = size;
            break;
        case 772:
            instruction->opCode = CALL;
            size = strlen(buff[1]);
            b = malloc(size);
            parseVariableName(b, 0, buff[1]);
            
            instruction->params = b;
            instruction->paramCount = size;
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