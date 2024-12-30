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
int parseValue(unsigned char* buff, int startIndex, void* value);

/**
 * Gets the value size for a certain type for a  parameter.
 * @param type the type's byte indentifier.
 */
inline int getValueSize(unsigned char type);

#endif