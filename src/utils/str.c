#include "utils.h"

void str_add(char **str, char const *add)
{
    int base_size = *str ? strlen(*str) : 0;
    int add_size = *add ? strlen(add) : 0;
    char *new_str = malloc(sizeof(char) * (base_size + add_size + 1));

    if (!add_size) {
        free(new_str);
        return;
    }
    for (int i = 0; i < base_size; ++i)
        new_str[i] = (*str)[i];
    for (int i = 0; i < add_size; ++i)
        new_str[base_size + i] = add[i];
    new_str[base_size + add_size] = '\0';
    if (*str)
        free(*str);
    *str = new_str;
}

int str_find(char const *str, char const *sub_str)
{
    size_t index = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (index == strlen(sub_str))
            return (i - index);
        else if (str[i] == sub_str[index])
            index++;
        else
            index = 0;
    }
    if (index == strlen(sub_str))
        return (strlen(str) - index);
    return (-1);
}

bool str_contain(char const *str, char const c)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return (1);
    return (0);
}

int str_count(char const *str, char const c)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            count++;
    return (count);
}