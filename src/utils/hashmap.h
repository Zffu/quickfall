/**
 * A simple hashmap implementation.
 */

#ifndef HASHMAP_H
#define HASHMAP_H

struct Bucket {
	void** values;
	int bucketSize;
};

struct Hashmap {
	int bucketSize;
	int maxBucketIndex;

	struct Bucket** buckets;
};

struct Hashmap* createHashmap(int bucketSize, int maxBucketIndex);
void hashPut(struct Hashmap* hashmap, int hash, void* value);
void* hashGet(struct Hashmap* hashmap, int hash);

#endif
