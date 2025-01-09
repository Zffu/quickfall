/**
 * QuickAssembly Value types parsing.
 */

#ifndef QASM_PARSER_VALUES_H
#define QASM_PARSER_VALUES_H

/**
 * Parses a 32-bit integer into bytes.
 * @param buff the buff to append the bytes to.
 * @param index the index of where to append the bytes.
 * @param str the string containing the integer.
 */
void parseInt32(void** buff, int index, char* str);


/**
 * Parses a variable name.
 * @param buff the buff to append the bytes to.
 * @param index the index of where to append the bytes.
 * @param str the string containing the variable name.
 */
void parseVariableName(void** buff, int index, char* str);

#endif