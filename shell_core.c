// shell_core.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell_core.h"
#include "utils.h"

int running = 1;

char *builtin_str[] = { "cd", "help", "exit" };
int (*builtin_func[])(char **) = { &smartshell_cd, &smartshell_help, &smartshell_exit };

int smartshell_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int smartshell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "SmartShell Error: Expected argument to \"cd\"\n");
    } else if (chdir(args[1]) != 0) {
        perror("SmartShell Error");
    }
    return 1;
}

int smartshell_help(char **args) {
    (void)args;
    printf("SmartShell: A simple AI-enhanced UNIX-like shell.\n");
    printf("Built-ins: cd, help, exit\n");
    return 1;
}

int smartshell_exit(char **args) {
    (void)args;
    running = 0;
    return 0;
}

int is_shell_running() {
    return running;
}

void exec_command(char **args, char **redir_argv, int wait, int res) {
    for (int i = 0; i < smartshell_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            (*builtin_func[i])(args);
            res = 1;
        }
    }

    if (res == 0) {
        int status;
        pid_t pid = fork();

        if (pid == 0) {
            if (res == 0) res = smartshell_redirect(args, redir_argv);
            if (res == 0) res = smartshell_pipe(args);
            if (res == 0) execvp(args[0], args);
            exit(EXIT_SUCCESS);
        } else if (pid < 0) {
            perror("SmartShell Error: Fork failed");
            exit(EXIT_FAILURE);
        } else {
            if (wait == 1) {
                waitpid(pid, &status, WUNTRACED);
            }
        }
    }
}

int handle_history_command(char *history, char **redir_args) {
    char *cur_args[BUFFER_SIZE];
    char cur_command[MAX_LINE_LENGTH];
    int t_wait;

    if (history[0] == '\0') {
        fprintf(stderr, "No commands in history\n");
        return 1;
    }
    strcpy(cur_command, history);
    printf("%s\n", cur_command);
    parse_command(cur_command, cur_args, &t_wait);
    int res = 0;
    exec_command(cur_args, redir_args, t_wait, res);
    return res;
}
