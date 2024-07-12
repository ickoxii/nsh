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

/** Builtin commands */
char *builtin_commands[] = {
    "cd",
    "help",
    "exit",
    "ls"
};

/** Function pointers for builtin commands **/
int (*builtin_funcs[])(char**) = {
    nsh_cd,
    nsh_help,
    nsh_exit,
    nsh_ls
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
    DEBUG_PRINT("Inside nsh_loop\n");

    char *line;
    char **args;
    int status;

    do {
        char *pwd = getcwd(NULL, 0);
        printf("%s> ", pwd);
        free(pwd);

        line = nsh_getline();               /* Read */

        DEBUG_PRINT("line: %s\n", line);

        args = nsh_tokenize(line);          /* Parse */

        DEBUG_PRINT_TOKENS(args);

        status = nsh_execute(args);         /* Execute */

        free(line);
        free(args);
    } while (status);
}

/** Builtins */

/**
 * nsh_ls
 *
 * List the contents of the current directory. If passed an argument,
 * list the contents of that directory.
 * */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int nsh_ls(char** args) {
    DEBUG_PRINT("Inside nsh_ls\n");
    DIR *dir;

    if(args[1] == NULL) {
        dir = opendir(".");
    } else {
        dir = opendir(args[1]);
    }

    if(dir == NULL) {
        fprintf(stderr, "Could not open directory\n");
        return 1;
    }

    struct dirent *entry;

    while((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return 1;
}
#pragma GCC diagnostic pop

/**
 * nsh_cd
 *
 * Change directories.
 * */
int nsh_cd(char** args) {
    DEBUG_PRINT("Inside nsh_cs\n");

    if(args[1] == NULL) {
        fprintf(stderr, "Expected argument to `cd`\n");
    } else if (chdir(args[1]) != 0) {
        fprintf(stderr, "Could not find directory %s\n", args[1]);
    }
    return 1;
}

/**
 * nsh_help
 *
 * Print help menu
 * */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int nsh_help(char** args) {
    DEBUG_PRINT("Inside nsh_help\n");

    printf("\nWelcome to nsh, the [N]ano [SH]ell!\n");
    printf("Below is a list of built-in commands:\n");
    for(int i = 0; i < NUM_BUILTINS; ++i) {
        printf("  %s\n", builtin_commands[i]);
    }
    printf("\n");

    return 1;
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int nsh_exit(char** args) {
    DEBUG_PRINT("Inside nsh_exit\n");

    return 0;
}
#pragma GCC diagnostic pop


/** Helpers */
/**
 * nsh_launch
 *
 * Launches a program (i.e. not a builtin function) and waits for it to execute.
 * */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wreturn-type"
int nsh_launch(char** args) {
#ifdef DEBUG
    printf("Inside nsh_launch\n");
#endif

    /* TODO */
    return 1;
}
#pragma GCC diagnostic pop

/**
 * nsh_get_line
 *
 * This function reads in a line from stdin and returns it. We do
 * not allow for a command to span multiple lines.
 * */
char* nsh_getline(void) {
    DEBUG_PRINT("Inside nsh_getline\n");

    char* line = malloc(NSH_BUFF_SIZE * sizeof(char));
    int buff_capacity = NSH_BUFF_SIZE;

    if(!line) {
        fprintf(stderr, "nsh_get_line malloc failed");
        exit(EXIT_FAILURE);
    }

    char ch;
    int buff_size = 0;
    for(;;) {
        ch = getchar();

        /* Read char */
        if(ch == '\n') {
            line[buff_size] = '\0';
            return line;
        } else {
            line[buff_size] = ch;
        }

        buff_size++;

        /* Realloc if overflowing */
        if(buff_size >= buff_capacity) {
            buff_capacity += NSH_BUFF_SIZE;
            line = (char*)realloc(line, (buff_capacity) * sizeof(char));
            if(!line) {
                fprintf(stderr, "realloc fail in getline\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return line;
}

/**
 * nsh_tokenize
 *
 * Tokenizes the line input by user.
 * */
char** nsh_tokenize(char* line) {
    DEBUG_PRINT("Inside nsh_tokenize\n");

    int buff_size = NSH_TOK_SIZE;
    char **tokens = malloc(buff_size * sizeof(char));
    char *token, **tokens_backup;

    if(!tokens) {
        fprintf(stderr, "realloc fail in tokenize\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, NSH_DELIMS);

    int ndx = 0;
    while(token != NULL) {
        tokens[ndx] = token;
        ndx++;

        if(ndx >= NSH_TOK_SIZE) {
            buff_size += NSH_TOK_SIZE;
            tokens_backup = tokens;

            tokens = realloc(tokens, buff_size * sizeof(char));

            if(!tokens) {
                fprintf(stderr, "you done fucked up realloc in tokenize\n");
                free(tokens_backup);
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, NSH_DELIMS);
    }

    tokens[ndx] = NULL;
    return tokens;
}

/**
 * nsh_execute
 *
 * Either calls a builtin function or launches a program.
 * */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wreturn-type"
int nsh_execute(char** args) {
    DEBUG_PRINT("Inside nsh_execute\n");

    if(args[0] == NULL) {
        printf("Empty command\n");
        printf("Call `help` for a list of supported commands\n");
        return 1;
    }

    for(int i = 0; i < NUM_BUILTINS; ++i) {
        if(strcmp(builtin_commands[i], args[0]) == 0) {
            DEBUG_PRINT("Calling %s from nsh_execute\n", buildin_commands[i]);
            return ((*builtin_funcs[i])(args));
        }
    }

    return nsh_launch(args);
}
#pragma GCC diagnostic pop
