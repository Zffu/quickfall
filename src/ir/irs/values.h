/**
 * IR for value related.
 */

#ifndef IR_VALUES_H
#define IR_VALUES_H

/**
 * Parses the value into the buffer.
 * @param buff the byte buffer.
 * @param startIndex the starting index of the buffer.
 * @param value the value to parse.
 */
void parseValue(unsigned char* buff, int startIndex, void* value);

#endif