#ifndef SHELL_CORE_H
#define SHELL_CORE_H

#define MAX_LINE_LENGTH 1024
#define BUFFER_SIZE 64
#define REDIR_SIZE 2
#define PIPE_SIZE BUFFER_SIZE
#define MAX_HISTORY_SIZE 128
#define MAX_COMMAND_NAME_LENGTH 128

#define TOFILE_DIRECT ">"
#define APPEND_TOFILE_DIRECT ">>"
#define FROMFILE "<"
#define PIPE_OPT "|"

int smartshell_cd(char **args);
int smartshell_help(char **args);
int smartshell_exit(char **args);
int smartshell_num_builtins();
int is_shell_running();
void exec_command(char **args, char **redir_argv, int wait, int res);
int handle_history_command(char *history, char **redir_args);

#endif
