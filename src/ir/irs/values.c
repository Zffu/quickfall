/**
 * IR for value related.
 */

#include <stdlib.h>

#include "../../parser/ast.h"

#include "../../parser/structs/values.h"
#include "../../parser/structs/tree.h"

/**
 * Parses the value into the buffer.
 * @param buff the byte buffer.
 * @param startIndex the starting index of the buffer.
 * @param value the value to parse.
 */
int parseValue(unsigned char* buff, int startIndex, void* value) {
    if(((AST_TREE_BRANCH*)value)->type == AST_TYPE_VALUE) {
        AST_VALUE* val = (AST_VALUE*) value;

        if(val->valueType == 0x01) { // int32
            int num = atoi(val->value);

            buff[startIndex + 1] = (num >> 24) & 0xFF;
            buff[startIndex + 2] = (num >> 16) & 0xFF;
            buff[startIndex + 3] = (num >> 8) & 0xFF;
            buff[startIndex + 4] = num & 0xFF;

            return startIndex + 4;
        }
    }

    return startIndex;
}

/**
 * Gets the value size for a certain type for a  parameter.
 * @param type the type's byte indentifier.
 */
inline int getValueSize(unsigned char type) {
    if(type == 0x01) return 4; // int32 type -> 4 bytes
    return 0;
}
