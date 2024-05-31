/******************************************************************************
 *
 * @file        nsh.c
 *
 * @author      Icko X Iben
 *
 * @date        Friday, 31 May 2024
 *
 * @brief       [N]ano [SH]ell
 *
 *****************************************************************************/

#include "nsh.h"

void nsh_loop(void) {
    printf("Hello world\n");
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void nsh_cd(char** argv) {

}

void nsh_help(char** argv) {

}

void nsh_exit(char** argv) {

}
#pragma GCC diagnostic pop
