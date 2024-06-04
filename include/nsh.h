/******************************************************************************
 *
 * @file        nsh.h
 *
 * @author      Icko X Iben
 *
 * @date        Friday, 31 May 2024
 *
 * @brief       [N]ano [SH]ell
 *
 *****************************************************************************/

#ifndef NSH_H
#define NSH_H

/** Includes **/
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Defines **/
typedef int Bool;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/** Prototypes */

void nsh_loop(void);
void nsh_cd(char**);
void nsh_help(char**);
void nsh_exit(char**);

#endif
