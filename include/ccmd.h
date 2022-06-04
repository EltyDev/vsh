#ifndef CCMD_H_
    #define CCMD_H_
    
    #include <stdlib.h>
    #include "shell.h"

typedef struct  custom_cmd_s {
    char *name;
    int (*function)(char **);
} custom_cmd_t;

#endif
