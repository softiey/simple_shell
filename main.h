#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* buffers */
#define RBSIZE 1024
#define WBSIZE 1024
#define BFLUSH -1

extern char **environ;
/**
 * struct liststr using singly linked list
 * @num: the number field
 * @str: a string
 * @next: always points to the next node
 */
typedef struct l_str
{
	int num;
	char *str;
	struct l_str *next;
} l_str_t;

/**
 *struct passinginfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinginfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	l_str_t *env;
	l_str_t *history;
	l_str_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} p_info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(p_info_t *);
} builtin_table;

int hsh(p_info_t *, char **);
int find_builtin(p_info_t *);
void find_cmd(p_info_t *);
void fork_cmd(p_info_t *);
int is_cmd(p_info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(p_info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
int _myalias(p_info_t *);
ssize_t get_input(p_info_t *);
int _getline(p_info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(p_info_t *);
void set_info(p_info_t *, char **);
void free_info(p_info_t *, int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(p_info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(p_info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(p_info_t *);
int _mycd(p_info_t *);
int _myhelp(p_info_t *);
int _myhistory(p_info_t *);
char *_getenv(p_info_t *, const char *);
int _myenv(p_info_t *);
int _mysetenv(p_info_t *);
int _myunsetenv(p_info_t *);
int populate_env_list(p_info_t *);
char **get_environ(p_info_t *);
int _unsetenv(p_info_t *, char *);
int _setenv(p_info_t *, char *, char *);
char *get_history_file(p_info_t *info);
int write_history(p_info_t *info);
int read_history(p_info_t *info);
ssize_t get_node_index(l_str_t *, l_str_t *);
int is_chain(p_info_t *, char *, size_t *);
void check_chain(p_info_t *, char *, size_t *, size_t, size_t);
int replace_alias(p_info_t *);
int replace_vars(p_info_t *);
int replace_string(char **, char *);
int build_history_list(p_info_t *info, char *buf, int linecount);
int renumber_history(p_info_t *info);
l_str_t *add_node(l_str_t **, const char *, int);
l_str_t *add_node_end(l_str_t **, const char *, int);
size_t print_list_str(const l_str_t *);
int delete_node_at_index(l_str_t **, unsigned int);
void free_list(l_str_t **);
size_t list_len(const l_str_t *);
char **l_str_to_strings(l_str_t *);
size_t print_list(const l_str_t *);
l_str_t *node_starts_with(l_str_t *, char *, char);

#endif

