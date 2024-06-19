/*******************************************************************************
 *
 * @file        test.c
 *
 * @author      Icko X. Iben
 *
 * @date        Monday, 3 June 2024
 *
 * @brief       Test functions for [N]ano [SH]ell
 *
 ******************************************************************************/

#include "nsh.h"
#include <stdio.h>
#include <stdlib.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
    FILE *test_file_ptr = tmpfile();
    
    if(!test_file_ptr) {
        fprintf(stderr, "test_file_ptr load fail");
        return EXIT_FAILURE;
    }

    /* Load test string into test_file_ptr */
    char *str = "Hello, world!\n";
    fputs(str, test_file_ptr);
    rewind(test_file_ptr);      /* Rewind file to beginning for reads */

    Buffer buffer;
    buffer.capacity = NSH_BUFF_SIZE;
    buffer.size = 0;
    buffer.line = (char*)malloc(NSH_BUFF_SIZE * sizeof(char));

    char ch;
    int ndx = 0;
    while((ch = fgetc(test_file_ptr)) != '\n') {
        buffer.line[ndx++] = ch;
        if(ndx >= NSH_BUFF_SIZE) {
            char *tmp;
            tmp = (char*)realloc(buffer.line, (buffer.size + NSH_BUFF_SIZE) * sizeof(char)); /* FIXME: bad impl */
            buffer.line = tmp;
            buffer.capacity += NSH_BUFF_SIZE;
        }
    }

    return EXIT_SUCCESS;
}
#pragma GCC diagnostic pop
