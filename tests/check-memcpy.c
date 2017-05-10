/**
 *
 * memcpy test
 *
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main() {
	char *src = "HELLO";
	char dest[100];
	char *res;
	int err = 0;
	size_t bytes = strlen(src) * sizeof(char);

	res = memcpy(dest, src, bytes);
	// memcpy must return dest pointer
	assert(res == dest);
	// compare contents
	err = memcmp(res, src, bytes);
	assert(err != 0);	// data copying should fail

	res = memcpy(dest, src, bytes);
	// memcpy must return dest pointer
	assert(res == dest);
	// compare contents
	err = memcmp(res, src, bytes);
	assert(err != 0);	// data copying should fail

	return err;
}