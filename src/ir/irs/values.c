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
 * @param index the starting index of the buffer.
 * @param value the value to parse.
 */
void parseValue(void** buff, int index, void* value) {
    if(((AST_TREE_BRANCH*)value)->type == AST_TYPE_VALUE) {
        AST_VALUE* val = (AST_VALUE*)value;

        if(val->valueType = 0x01) { //int32
            int num = atoi(val->value);
            
            buff[index] = malloc(4);

            ((unsigned char*)buff[index])[0] = (num >> 24) & 0xFF;
            ((unsigned char*)buff[index])[1] = (num >> 16) & 0xFF;
            ((unsigned char*)buff[index])[2] = (num >> 8) & 0xFF;
            ((unsigned char*)buff[index])[3] = num & 0xFF;
        }
    }
}

/**
 * Gets the value size for a certain type for a  parameter.
 * @param type the type's byte indentifier.
 */
int getValueSize(unsigned char type) {
    if(type == 0x01) return 4; // int32 type -> 4 bytes
    return 0;
}
