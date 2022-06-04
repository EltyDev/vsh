#ifndef UTILS_H_
    #define UTILS_H_
    #define BUFFER_SIZE 10000

    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>

void str_add(char **str, char const *add);
char *input(char const *prompt);
void *memalloc(size_t const size, unsigned int const nb);
int array_len(char **array);
void array_destroy(char **array);
void array_add(char ***array, char *str);
int str_find(char const *str, char const *sub_str);
int str_contain(char const *str, char const c);

#endif
