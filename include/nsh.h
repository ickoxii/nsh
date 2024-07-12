/******************************************************************************
 *
 * @file        nsh.h
 *
 * @author      Icko X. Iben
 *
 * @date        Friday, 31 May 2024
 *
 * @brief       [N]ano [SH]ell
 *
 *****************************************************************************/

#ifndef NSH_H_
#define NSH_H_

/** Includes **/
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/** Defines **/
typedef int Bool;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define NSH_BUFF_SIZE 1024
#define NSH_DELIMS " \t\r\n\a"
#define NSH_TOK_SIZE 64
#define NUM_BUILTINS 4

/** Big debugger guy */
#ifdef DEBUG
#define DEBUG_PRINT(...) fprintf(stdout, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) do {} while(0)
#endif

#ifdef DEBUG
#define DEBUG_PRINT_ERR(...) fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG_PRINT_ERR(...) do {} while(0)
#endif

#ifdef DEBUG
#define DEBUG_PRINT_TOKENS(args) do {\
    int pos = 0;\
    DEBUG_PRINT("tokens\n");\
    while(args[pos] != NULL) {\
        DEBUG_PRINT("tok[%d]: %s\n", pos, args[pos]);\
        ++pos;\
    }\
} while(0)
#else
#define DEBUG_PRINT_TOKENS(args) do {} while(0)
#endif

/** Prototypes **/
void nsh_loop(void); /** Main loop **/

/** Commands **/
int nsh_cd(char**);         /* Change directory */
int nsh_help(char**);       /* Help function */
int nsh_exit(char**);       /* Terminate shell */
int nsh_ls(char**);         /* List directory */

/** Helpers **/
int nsh_launch(char**);     /* Launch program */
char* nsh_getline(void);    /* Read line from stdin */
char** nsh_tokenize(char*); /* Parse command */
int nsh_execute(char**);    /* Execute command */

#endif
