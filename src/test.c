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

#define SIZE (sizeof(buff) / sizeof(buff[0])) /* Terrible, only use for arrays, not malloc'd pointers */

typedef struct {
    char *str;
    int size;
} Buffer;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
    FILE *test_file_ptr = tmpfile();
    
    if(!test_file_ptr) {
        perror("test_file_ptr load fail");
        return EXIT_FAILURE;
    }

    /* Load test string into test_file_ptr */
    char *str = "Hello, world!\n";
    fputs(str, test_file_ptr);
    rewind(test_file_ptr);      /* Rewind file to beginning for reads */

    char *buff = (char*)malloc(NSH_BUFF_SIZE * sizeof(char));

    char ch;
    int ndx = 0;
    while((ch = fgetc(test_file_ptr)) != '\n') {
        buff[ndx++] = ch;
        if(ndx >= NSH_BUFF_SIZE) {
            char *tmp;
            tmp = (char*)realloc(buff, (SIZE + NSH_BUFF_SIZE) * sizeof(char));
            buff = tmp;
        }
    }

    return EXIT_SUCCESS;
}
#pragma GCC diagnostic pop
