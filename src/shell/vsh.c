#include "shell.h"
#include "ccmd.h"
#include "env.h"

void shell_destroy(shell_t *shell)
{   
    if (shell->path)
        free(shell->path);
    if (!shell)
        return;
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
        } else if (command[i] != ' ' && command[i] != '\t')
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
    if (!shell->argv || !shell->argv[0])
        return;
    is_custom_command(shell, shell->argv[0]);
    find_path(shell);
    if (!shell->path && !shell->is_custom) {
        printf("%s: command not found\n", shell->argv[0]);
        return;
    }
    if (!fork())
        shell->command.execute(shell->path, shell->argv, shell->env);
    else
        waitpid(0, &shell->exit_code, 0);
    return;
}


void init_command(shell_t *shell, char *command)
{   
    if (shell->path)
        free(shell->path);
    if (shell->argv) {
        array_destroy(shell->argv);
        shell->argv = NULL;
    } if (command)
        parsing_args(shell, command);
    shell->is_exit = false;
    shell->is_custom = false;
    shell->exit_code = 0;
    free(command);
}

char *handling_input()
{   
    char *command = input("$> ");
    int index = 0;
    bool double_quote = false;
    bool single_quote = false;
    bool bracket = false;

    for (int i = 0; command[i]; ++i) {
        if (command[i] == '\"') {
            if (double_quote)
                double_quote = false;
            else if (!single_quote)
                double_quote = true;
        } else if (command[i] == '\'') {
            if (single_quote)
                single_quote = false;
            else if (!double_quote)
                single_quote = true;
        } else if (command[i] == '$' && command[i + 1] == '{')
            bracket = true;
        else if (command[i] == '}') {
            if (double_quote || single_quote)
            bracket = false;
        }
    }
    while (single_quote || double_quote || bracket) {
        index = strlen(command);
        str_add(&command, "\n");
        str_add(&command, input("> "));
        for (int i = index; command[i]; ++i) {
            if (command[i] == '\"') {
                if (double_quote)
                    double_quote = false;
                else if (!single_quote)
                    double_quote = true;
            } else if (command[i] == '\'') {
                if (single_quote)
                    single_quote = false;
                else if (!double_quote)
                    single_quote = true;
            } else if (command[i] == '$' && command[i + 1] == '{')
                bracket = true;
            else if (command[i] == '}') {
                if (double_quote || single_quote)
                    bracket = false;
            }
        }
    }
    return (command);
}

int main(int argc, char **argv, char **env)
{
    UNUSED(argc);
    UNUSED(argv);
    shell_t *shell = memalloc(sizeof(shell_t), 1);
    shell->env = env;

    while (!shell->is_exit) {
        init_command(shell, handling_input());
        execute_command(shell);
    }
    shell_destroy(shell);
    return (0);
}
