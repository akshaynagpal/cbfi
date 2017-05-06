/**
 *
 *  getnetentbyname() testing
 *
 **/

#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
    struct netent *entry;
    entry = getnetbyname("link-local");;
    assert(entry == NULL);
    entry = getnetbyname("link-local");
    assert(entry == NULL);
    return errno;
}