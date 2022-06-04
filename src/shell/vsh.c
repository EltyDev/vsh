#include "shell.h"

void shell_destroy(shell_t *shell)
{
    if (!shell)
        return;
    if (shell->command)
        free(shell->command);
    if (shell->argv)
        array_destroy(shell->argv);
    free(shell);
}

void parsing_args(shell_t *shell, char *command)
{   
    char quote_type = '\0';
    char *arg = NULL;

    for (int i = 0; command[i]; ++i) {
        if (command[i] == '\'' || command[i] == '\"') {
            quote_type = command[i];
            for (++i; command[i] != quote_type && command[i]; ++i)
                str_add(&arg, (char[2]) {command[i], 0});
        } else
            str_add(&arg, (char[2]) {command[i], 0});
        if (command[i] == ' ' || command[i] == '\t') {
            array_add(&shell->argv, arg);
            arg = NULL;
        }
    }
    array_add(&shell->argv, arg);
}


void execute_command(shell_t *shell)
{
    if (!shell->command)
        return;
    return;
}


void init_command(shell_t *shell, char *command)
{   
    if (shell->command) {
        free(shell->command);
        shell->command = NULL;
    } if (shell->argv) {
        array_destroy(shell->argv);
        shell->argv = NULL;
    } if (command) {
        parsing_args(shell, command);
        shell->command = strdup(shell->argv[0]);
    }
    shell->is_exit = false;
    shell->is_custom = false;
    shell->exit_code = 0;
    free(command);
}

int main(int argc, char **argv, char **env)
{
    UNUSED(argc);
    UNUSED(argv);
    shell_t *shell = memalloc(sizeof(shell_t), 1);
    shell->env = env;

    while (!shell->is_exit) {
        init_command(shell, input("$> "));
        execute_command(shell);
    }
    shell_destroy(shell);
    return (0);
}
