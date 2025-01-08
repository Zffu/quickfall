/**
 * The writer of QuickAssembly. The inline assembly of Quickfall.
 */

#include <stdio.h>

#include "../../ir/structs.h"

#ifndef QASM_WRITER_H
#define QASM_WRITER_H

/**
 * Writes some standart QuickAssembly code equivalent to the parsed IR.
 * @param fptr the file output.
 * @param output the output of the IR convertor.
 */
void writeQASM(FILE* fptr, IR_OUTPUT* output);

#endif