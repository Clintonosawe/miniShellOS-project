// utils.c
#define _GNU_SOURCE
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"

#define PROMPT_MAX_LENGTH 30
#define PROMPT_FORMAT "%F %T "

void init_shell(void) {
    printf("\n");
    printf("   _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ \n");
    printf("  |     |     |     |     |     |     |     |     |     |     |\n");
    printf("  |  S  |  M  |  A  |  R  |  T  |  S  |  H  |  E  |  L  |  L  |\n");
    printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
    printf("  |                                                           |\n");
    printf("  |   ███████╗███╗   ███╗ █████╗ ██████╗ ███████╗██╗  ██╗    |\n");
    printf("  |   ██╔════╝████╗ ████║██╔══██╗██╔══██╗██╔════╝██║  ██║    |\n");
    printf("  |   ███████╗██╔████╔██║███████║██████╔╝███████╗███████║    |\n");
    printf("  |   ╚════██║██║╚██╔╝██║██╔══██║██╔══██╗╚════██║██╔══██║    |\n");
    printf("  |   ███████║██║ ╚═╝ ██║██║  ██║██║  ██║███████║██║  ██║    |\n");
    printf("  |   ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝    |\n");
    printf("  |___________________________________________________________|\n");
    printf("\n");
    
    char *username = getenv("USER");
    printf("Current user: @%s\n", username);
    printf("\n");
}

char *get_current_dir(void) {
    static char cwd[PATH_MAX];
    return getcwd(cwd, sizeof(cwd));
}

char *get_prompt(void) {
    static char _prompt[PROMPT_MAX_LENGTH];
    time_t now = time(NULL);
    struct tm *tmp = localtime(&now);

    if (strftime(_prompt, sizeof(_prompt), PROMPT_FORMAT, tmp) == 0) {
        strcpy(_prompt, "??? ");
    }

    char *username = getenv("USER");
    strncat(_prompt, username, sizeof(_prompt) - strlen(_prompt) - 1);
    return _prompt;
}

void read_line(char *line) {
    char *ret = fgets(line, MAX_LINE_LENGTH, stdin);
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\n') {
            line[i] = '\0';
            break;
        }
    }
    if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0 || ret == NULL) {
        exit(EXIT_SUCCESS);
    }
}

void parse_command(char *input_string, char **argv, int *wait) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        argv[i] = NULL;
    }

    *wait = 1;
    if (input_string[strlen(input_string) - 1] == '&') {
        *wait = 0;
        input_string[strlen(input_string) - 1] = '\0';
    }

    int i = 0;
    argv[i] = strtok(input_string, " ");
    while (argv[i] != NULL) {
        i++;
        argv[i] = strtok(NULL, " ");
    }
}

void set_prev_command(char *history, char *line) {
    strcpy(history, line);
}

int smartshell_redirect(char **args, char **redir_argv) {
    (void)args;
    (void)redir_argv;
    return 0;
}

int smartshell_pipe(char **args) {
    (void)args;
    return 0;
}
