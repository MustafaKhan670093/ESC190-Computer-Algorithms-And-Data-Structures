#include "csc190_utils.h"
void mallocS(void** ptr, size_t size)
{
    *ptr = malloc(size);
    if (ptr==NULL)
        printf("failed to allocate memory of %lluMB\n", (ull)size>>20);
    assert(ptr);
}