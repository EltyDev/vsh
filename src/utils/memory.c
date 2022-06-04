#include "utils.h"

void *memalloc(size_t const size, unsigned int const nb)
{   
    char *ptr = malloc(size * nb);

    for (unsigned int i = 0; i < nb * size; ++i)
        *(ptr + i) = 0;
    return (ptr);
}