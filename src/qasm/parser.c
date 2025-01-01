/**
 * The parser of QuickAssembly. The inline assembly of Quickfall.
 */

#include <stdlib.h>

#include "./parser.h"

#include "../parser/structs/functions.h"

#include "../ir/structs.h"
#include "../ir/ir.h"

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

}