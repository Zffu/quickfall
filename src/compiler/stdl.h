/**
 * The code in charge of managing the standart library usage in Quickfall.
 */

#ifndef COMPILER_STDL
#define COMPILER_STDL

#include "./compiler.h"

/**
 * Loads a component (a file) of the standart library and dump its content into the assembly output.
 * @param ctx the compiling context of the currently running compiling.
 * @param component the component name (file name) of the part to load.
 */
void loadAndDump(struct CompilingContext ctx, char* component);

#endif
