/**
 * IR for value related.
 */

#include <string.h>

#include "../../parser/ast.h"

#include "../../parser/structs/values.h"
#include "../../parser/structs/tree.h"

/**
 * Parses the value into the buffer.
 * @param buff the byte buffer.
 * @param startIndex the starting index of the buffer.
 * @param value the value to parse.
 */
void parseValue(unsigned char* buff, int startIndex, void* value) {
    if(((AST_TREE_BRANCH*)value)->type == AST_TYPE_VALUE) {
        AST_VALUE* val = (AST_VALUE*) value;

        if(val->valueType == 0x01) { // int32
            int num = atoi(val->value);

            buff[startIndex + 1] = (num >> 24) & 0xFF;
            buff[startIndex + 2] = (num >> 16) & 0xFF;
            buff[startIndex + 3] = (num >> 8) & 0xFF;
            buff[startIndex + 4] = num & 0xFF;
        }
    }
}