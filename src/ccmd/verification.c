#include "ccmd.h"

command_t commands[] = {
    {NULL, NULL}
};

void is_custom_command(shell_t *shell, char *command)
{
    for (int i = 0; commands[i].name; ++i) {
        if (strcmp(commands[i].name, command) == 0) {
            shell->is_custom = true;
            shell->command = commands[i];
            return;
        }
    }
    shell->is_custom = false;
    shell->command = (command_t) {"execve", &execve};
}