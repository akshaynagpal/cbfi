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

// struct to maintain counts of calls
typedef struct
{
    unsigned long fopen;
    unsigned long printf;
    unsigned long malloc;
    unsigned long calloc;
    unsigned long chdir;
    unsigned long connect;
    unsigned long open;
    unsigned long close;
    unsigned long fclose;
    unsigned long fgetc;
    unsigned long fputc;
} call_counts;

/**
 * global variable to maintain counts
 *
 *  declare static call_counts global_counts in exactly one .c file
 *
 * Declaration in wrap-fopen.c
 */
extern call_counts global_counts;
