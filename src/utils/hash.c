/**
 * Hashing related utilities.
 */

/**
 * Hashes a string.
 */
unsigned int hashstr(char* str) {
	unsigned int result = 5381;
	unsigned char* p;

	p = (unsigned char *)str;

	while(*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}

	return result;
}
