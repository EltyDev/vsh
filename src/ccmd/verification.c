#include "ccmd.h"

custom_cmd_t *custom_cmds[] = {
    NULL
};

void is_custom_command(shell_t *shell, char *command)
{
    if (command[0] == '!') {
        shell->is_custom = true;
        shell->command = strdup(command + 1);
    }
}