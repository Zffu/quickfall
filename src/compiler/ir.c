/**
 * The compiler's internal IR.
 */

#include <stdlib.h>

#include "../utils/hashmap.h"

/**
 * Creates an IR node based on the type and the name given.
 * @param type the IR type of the node.
 * @param nodeName the name of the IR node.
 */
IR_NODE* createIRNode(IR_TYPE type, char* nodeName) {
	IR_NODE* node = malloc(sizeof(IR_NODE));
	
	node->nodeType = type;
	node->nodeName = nodeName;

	node->variableIndex = 0;

	if(type == IR_FUNCTION) {
		node->variableHashmap = createHashmap(512, 50);
	}

	return node;
}
