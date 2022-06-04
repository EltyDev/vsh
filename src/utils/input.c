#include "utils.h"

#include <stdio.h>

char *input(char const *prompt)
{
    char *response = NULL;
    char *buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    ssize_t byte = 0;

    if (!write(1, prompt, strlen(prompt))) {
        free(buffer);
        return (NULL);
    }
    byte = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    buffer[byte] = '\0';
    while (byte == BUFFER_SIZE) {
        str_add(&response, buffer);
        free(buffer);
        buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        byte = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        buffer[byte] = '\0';
    }
    if (byte > 0 && buffer[byte - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    str_add(&response, buffer);
    free(buffer);
    return (response);
}