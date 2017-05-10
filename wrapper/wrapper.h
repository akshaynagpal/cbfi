/**
 *
 * Wrapper linked library header file
 *
 **/

#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <execinfo.h>
#include <netdb.h>
#include <stdarg.h>
#include <dirent.h>


// struct to maintain counts of calls
typedef struct
{
    unsigned long fopen;
    unsigned long printf;
    unsigned long malloc;
    unsigned long calloc;
    unsigned long chdir;
    unsigned long chmod;
    unsigned long chown;
    unsigned long connect;
    unsigned long dup;
    unsigned long dup2;
    unsigned long open;
    unsigned long close;
    unsigned long fclose;
    unsigned long fgetc;
    unsigned long fgets;
    unsigned long fscanf;
    unsigned long fread;
    unsigned long fwrite;
    unsigned long fseek;
    unsigned long fork;
    unsigned long fputc;
    unsigned long fputs;
    unsigned long fprintf;
    unsigned long getnetent;
    unsigned long getnetbyaddr;
    unsigned long getnetbyname;
    unsigned long kill;
    unsigned long lseek;
    unsigned long memcpy;
    unsigned long memcmp;
    unsigned long getc;
    unsigned long gets;
    unsigned long read;
    unsigned long system;
    unsigned long opendir;
} call_counts;

/**
 * global variable to maintain counts
 *
 *  declare static call_counts global_counts in exactly one .c file
 *
 * Declaration in wrap-fopen.c
 */
extern call_counts global_counts;


/**
 *
 * Signatures for common functions
 *
 * Function definitions in common.c
 */
// custom malloc function
typedef void* (*orig_malloc_type)(size_t size);
// parse comma separated string of integers
unsigned int parse_fail_str(unsigned int **numbers, const char *failstr);

// check if gcov flush
int btrace_has_gcov(void);
