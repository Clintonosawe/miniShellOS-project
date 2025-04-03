// main.c (SmartShell entry point)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_core.h"
// #include "ai_handler.h"  // AI integration will be added later
#include "utils.h"

#define MAX_LINE_LENGTH 1024
#define BUFFER_SIZE 64
#define REDIR_SIZE 2

int main(void) {
    char *args[BUFFER_SIZE];
    char line[MAX_LINE_LENGTH];
    char t_line[MAX_LINE_LENGTH];
    char history[MAX_LINE_LENGTH] = "No commands in history";
    char *redir_argv[REDIR_SIZE];
    int wait;
    int res = 0;

    init_shell();

    while (is_shell_running()) {
        printf("%s:%s> ", get_prompt(), get_current_dir());
        fflush(stdout);

        read_line(line);
        strcpy(t_line, line);
        parse_command(line, args, &wait);

        if (args[0] == NULL) continue;

        if (strcmp(args[0], "!!") == 0) {
            res = handle_history_command(history, redir_argv);
        }

        // Future GPT integration will go here:
        // else if (strcmp(args[0], "ai") == 0) {
        //     ai_command(args);
        // }

        else {
            set_prev_command(history, t_line);
            exec_command(args, redir_argv, wait, res);
        }

        res = 0;
    }

    return 0;
}
