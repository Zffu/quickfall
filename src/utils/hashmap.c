/**
 * A simple hashmap implementation.
 */

#include <stdlib.h>

#include "./hashmap.h"

struct Hashmap* createHashmap(int bucketSize, int maxBucketIndex) {
	struct Hashmap* map = malloc(sizeof(struct Hashmap));
	map->bucketSize = bucketSize;
	map->maxBucketIndex = maxBucketIndex;

	map->buckets = malloc(sizeof(struct Bucket*) * maxBucketIndex);
	
	for(int i = 0; i < maxBucketIndex; ++i) {
		map->buckets[i] = NULL;
	}

	return map;
}

void hashPut(struct Hashmap* hashmap, int hash, void* value) {
	int bucket = hash / hashmap->bucketSize;

	if(hashmap->buckets[bucket] == NULL) {
		struct Bucket* b = malloc(sizeof(struct Bucket));
		b->bucketSize = hashmap->bucketSize;
		b->values = malloc(sizeof(int*) * b->bucketSize);

		hashmap->buckets[bucket] = b;
	}

	hashmap->buckets[bucket]->values[hash % hashmap->bucketSize] = value;
}

void* hashGet(struct Hashmap* hashmap, int hash) {
	int bucket = hash / hashmap->bucketSize;
	
	if(hashmap->buckets[bucket] == NULL) return NULL;

	return hashmap->buckets[bucket]->values[hash % hashmap->bucketSize];
}

