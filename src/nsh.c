/******************************************************************************
 *
 * @file        nsh.c
 *
 * @author      Icko X. Iben
 *
 * @date        Friday, 31 May 2024
 *
 * @brief       [N]ano [SH]ell
 *
 *****************************************************************************/

#include "nsh.h"
#include <stdlib.h>

/** Builtin commands */
char *builtin_commands[] = {
    "cd",
    "help",
    "exit"
};


 /**
  * @brief Main loop
  *
  * The main loop has three basic steps:
  *   1. **Read**: Read a command from stdin.
  *   2. **Parse**: Parse the command into a program and arguments.
  *   3. **Execute**: Run the parsed command.
  * */
void nsh_loop(void) {
    char **args;
    int status;

    do {
        char *pwd = getcwd(NULL, 0);
        printf("%s> ", pwd);
        free(pwd);

        Buffer buffer = nsh_get_line();     /* Read */
        args = nsh_parse(buffer.line);      /* Parse */
        status = nsh_execute(args);         /* Execute */

        #ifdef DEBUG
        printf("%s\n", buffer.line);
        #endif

        free(buffer.line);
        /* free(args); */
    } while (status);
}

/** Builtins */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int nsh_cd(char** argv) {
    // TODO
    return 1;
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int nsh_help(char** argv) {
    // TODO
    return 1;
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int nsh_exit(char** argv) {
    return 0;
}
#pragma GCC diagnostic pop


/** Helpers */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wreturn-type"
int nsh_launch(char** args) {
    // TODO
    return 1;
}
#pragma GCC diagnostic pop

 /**
  * nsh_get_line
  *
  * This function reads in a line from stdin and returns it. We do
  * not allow for a command to span multiple lines.
  * */
char* nsh_get_line(void) {
    char *line = malloc(NSH_BUFF_SIZE * sizeof(char));

    char ch = '\0';
    int ndx = 0;
    while ((ch = getchar()) != '\n') {
        line[ndx++] = ch;
    }

    return line;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wreturn-type"
char** nsh_parse(char* line) {
    // TODO
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wreturn-type"
int nsh_execute(char** args) {
    // TODO
}
#pragma GCC diagnostic pop

Buffer init_buffer(void) {
    Buffer buffer;
    buffer.size = 0;
    buffer.capacity = NSH_BUFF_SIZE;
    buffer.line = malloc(NSH_BUFF_SIZE * sizeof(char));
    return buffer;
}
