#include "utils.h"

void array_add(char ***array, char *str)
{
    int len = array_len(*array);
    char **new_array = malloc(sizeof(char *) * (len + 2));

    for (int i = 0; i < len; ++i)
        new_array[i] = (*array)[i];
    new_array[len] = str;
    new_array[len + 1] = NULL;
    free(*array);
    *array = new_array;
}

int array_len(char **array)
{
    int len = 0;

    for (; array && array[len]; len++);
    return (len);
}

void array_destroy(char **array)
{
    for (int i = 0; array[i]; ++i)
        free(array[i]);
    free(array);
}