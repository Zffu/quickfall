/**
 * The writer of QuickAssembly. The inline assembly of Quickfall.
 */

#include <stdio.h>

#include "../../ir/structs.h"

/**
 * Writes some standart QuickAssembly code equivalent to the parsed IR.
 * @param fptr the file output.
 * @param output the output of the IR convertor.
 */
void writeQASM(FILE* fptr, IR_OUTPUT* output) {
    for(int i = 0; i < output->blockCount + 1; ++i) {
        fprintf(fptr, "%d:\n", i);
    }
}