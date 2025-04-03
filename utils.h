// utils.h
#ifndef UTILS_H
#define UTILS_H

#define MAX_LINE_LENGTH 1024
#define BUFFER_SIZE 64

void init_shell(void);
char *get_prompt(void);
char *get_current_dir(void);
void read_line(char *line);
void parse_command(char *input_string, char **argv, int *wait);
void set_prev_command(char *history, char *line);
int smartshell_redirect(char **args, char **redir_argv);
int smartshell_pipe(char **args);

#endif
