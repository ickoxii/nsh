/******************************************************************************
 * 
 * @file        main.c
 *
 * @author      Icko X. Iben
 *
 * @date        Friday, 31 May 2024
 *
 * @brief       [N]ano [SH]ell
 *
 *****************************************************************************/

/** Includes **/
#include "nsh.h"
#include "logger.h"
#include <assert.h>

FILE *logFile = NULL;

 /**
  * @brief  Main entrypoint
  * 
  * @param  argc    Argument count
  * @param  argv    Argument vector
  * @return status code
  * */
static_assert(TRUE, "Dummy declaration to workaround https://github.com/clangd/clangd/issues/1167");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
    /* Are we cooking? */
#ifdef DEBUG
    logFile = fopen(LOG_FILE_NAME, "a"); /* Open in append mode */
    printf("Debug mode enabled\n");
#endif

    /* Load config files */

    /* Enter shell loop */
    nsh_loop();

    /* Free memory and terminate */

    return EXIT_SUCCESS;
}
#pragma GCC diagnostic pop
