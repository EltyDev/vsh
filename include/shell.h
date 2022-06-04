#ifndef SHELL_H_
    #define SHELL_H_

    #include "utils.h"
    #include <stdio.h>
    #include <stdbool.h>

    #define UNUSED(x) (void)(x)

typedef struct shell_s {
    char *command;
    char **argv;
    char **env;
    bool is_exit;
    bool is_custom;
    int exit_code;
} shell_t;

#endif
