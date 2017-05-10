/**
 *
 * memcmp test
 *
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main() {
	char *s1 = "HELLO";
	char *s2 = "HELLO";
	int err = 0;

	// memcmp must return 0
	// on failure return MEMCMP_FAIL value passed
	// through env flag
	err = memcmp(s1, s2, strlen(s1));
	assert(err == 1);	// first fail

	err = memcmp(s1, s2, strlen(s1));
	assert(err == 2);	// second fail

	err = memcmp(s1, s2, strlen(s1));
	assert(err == 3);

	return 0;
}