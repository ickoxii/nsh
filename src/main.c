/******************************************************************************
 * 
 * @file        main.c
 *
 * @author      Icko X Iben
 *
 * @date        Friday, 31 May 2024
 *
 * @brief       [N]ano [SH]ell
 *
 *****************************************************************************/

/** Includes */
#include "nsh.h"


/** Supported commands */
char *commands[] = {
    "cd",
    "help",
    "exit"
};


 /**
  * @brief  Main entrypoint
  * 
  * @param  argc    Argument count
  * @param  argv    Argument vector
  * @return status code
  * */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
    /** Load config files */

    /** Enter shell loop */
    nsh_loop();

    /** Free memory and terminate */

    return EXIT_SUCCESS;
}
#pragma GCC diagnostic pop
