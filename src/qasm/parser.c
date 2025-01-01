/**
 * The parser of QuickAssembly. The inline assembly of Quickfall.
 */

#include <stdlib.h>

#include "../parser/structs/functions.h"
#include "../ir/structs.h"

/**
 * Parses QuickAssembly instructions.
 */
void parseQAsmInstructions(IR_FUNCTION func, char* buff, int size) {
    char* wordBuff = malloc(32);
    int wordBuffIndex = 0;

    for(int i = 0; i < size; ++i) {
        char c = buff[i];

        if(c == '\0') break;
        
        if(c == '\n') {
            //todo: add singular instuction parsing.
        }
        else {
            wordBuff[wordBuffIndex] = c;
            ++wordBuffIndex;
        }        
    }
}
