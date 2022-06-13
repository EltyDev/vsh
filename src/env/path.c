#include "env.h"

void find_path(shell_t *shell)
{   
    char *path = strdup(getenv("PATH"));
    char *path_token = strtok(path, ":");
    char *path_dupe = NULL;

    shell->path = NULL;
    if (shell->is_custom)
        return;
    while (path_token) {
        path_dupe = strdup(path_token);
        str_add(&path_dupe, "/");
        str_add(&path_dupe, shell->argv[0]);
        if (access(path_dupe, F_OK) == 0) {
            shell->path = path_dupe;
            break;
        }
        path_token = strtok(NULL, ":");
        free(path_dupe);
    }
    free(path);
}