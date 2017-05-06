/**
 *
 *  getnetentbyname() testing
 *
 **/

#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <assert.h>

#define LINK_LOCAL 2851995648

int main(int argc, char const *argv[])
{
    struct netent *entry;
    entry = getnetbyaddr(LINK_LOCAL, AF_INET);
    assert(entry == NULL);
    entry = getnetbyaddr(LINK_LOCAL, AF_INET);
    assert(entry == NULL);
    return errno;
}