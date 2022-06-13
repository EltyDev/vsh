#ifndef SHELL_H_
#define SHELL_H_

#include "utils.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define UNUSED(x) (void)(x)

typedef struct command_s {
    char *name;
    int (*execute)(char const *, char * const [], char * const []);
} command_t;

typedef struct shell_s {
    char *path;
    command_t command;
    char **argv;
    char **env;
    bool is_exit;
    bool is_custom;
    int exit_code;
} shell_t;

#endif
