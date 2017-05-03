/**
 *
 * Test multiple libc calls
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv) {

    char read[100];
    int ret;

    // test malloc
    int *mal = (int *)malloc(sizeof(int));
    assert(mal != NULL);
    free(mal);

    // test calloc
    int *cal = (int *)calloc(1, sizeof(int));
    assert(cal != NULL);
    free(cal);

    // test malloc 2nd time
    mal = (int*)malloc(sizeof(int));
    assert(mal != NULL);
    free(mal);

    // test fopen
    FILE *fp = fopen("foo.txt", "w");
    assert(fp != NULL);
    fprintf(fp, "%s\n", "hello world");
    fclose(fp);

    // test chdir
    int x = chdir("..");
    assert(x == 0);

    // test calloc 2nd time
    cal = (int *)calloc(1, sizeof(int));
    assert(cal != NULL);
    free(cal);

    // test fopen 2nd time
    fp = fopen("foo.txt", "r");
    assert(fp != NULL);
    fscanf(fp, "%s", read);

    // test printf
    ret = printf("%s\n", read);
    assert(ret == (int)strlen(read));
    fclose(fp);

    return 0;
}
