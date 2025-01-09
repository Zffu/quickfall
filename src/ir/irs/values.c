/**
 * IR for value related.
 */

#include <stdlib.h>

#include "../../parser/ast.h"

#include "../../parser/structs/values.h"
#include "../../parser/structs/tree.h"

#include "../../lib/types.h"

/**
 * Parses the value into the buffer.
 * @param buff the byte buffer.
 * @param index the starting index of the buffer.
 * @param value the value to parse.
 */
void parseValue(void** buff, int index, void* value) {
    if(((AST_TREE_BRANCH*)value)->type == AST_TYPE_VALUE) {
        AST_VALUE* val = (AST_VALUE*)value;

        switch(*val->valueType) {
            case INT32:
                int num = atoi(val->value);
                buff[index] = malloc(4);

                ((unsigned char*)buff[index])[0] = (num >> 24) & 0xFF;
                ((unsigned char*)buff[index])[1] = (num >> 16) & 0xFF;
                ((unsigned char*)buff[index])[2] = (num >> 8) & 0xFF;
                ((unsigned char*)buff[index])[3] = num & 0xFF;

                break;
            
            case INT24:
                int num = atoi(val->value);
                buff[index] = malloc(3);

                ((unsigned char*)buff[index])[0] = (num >> 16) & 0xFF;
                ((unsigned char*)buff[index])[1] = (num >> 8) & 0xFF;
                ((unsigned char*)buff[index])[2] = num & 0xFF;
                break;
            
            case INT16:
                int num = atoi(val->value);
                buff[index] = malloc(2);

                ((unsigned char*)buff[index])[0] = (num >> 8) & 0xFF;
                ((unsigned char*)buff[index])[1] = num & 0xFF;
                break;
            
            case INT8:
                int num = atoi(val->value);
                buff[index] = malloc(1);
                ((unsigned char*)buff[index])[0] = num & 0xFF;
                break;

        }
    }
}

/**
 * Gets the value size for a certain type for a  parameter.
 * @param type the type's byte indentifier.
 */
int getValueSize(unsigned char type) {
    switch(type) {
        case INT32:
            return 32;
        case INT24:
            return 24;
        case INT16:
            return 16;
        case INT8:
            return 8;

    }
    return 0;
}
