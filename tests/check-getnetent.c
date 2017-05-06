/**
 *
 *  getnetent() testing
 *
 **/

#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
    struct netent *entry;
    entry = getnetent();
    assert(entry == NULL);
    entry = getnetent();
    assert(entry == NULL);
    return errno;
}