#ifndef SHELL_H

typedef struct command_t {
    char* name;
    void (*func) (char * param);
    char* description;
} command_t;

void run_shell();

#endif