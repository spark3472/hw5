#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

#define SUCCESS 0                                                                           
#define FAIL -1
#define TRUE 1
#define FALSE 0

int main() {
    printf("Testing Null Pointer\n");
    if(Mem_Free(NULL, 0) == -1)
    {
        printf("Did not free null pointer\n");
        exit(EXIT_SUCCESS);
    }else
    {
        printf("Freed a null pointer (this is not possible)\n");
        exit(EXIT_FAILURE);
        
    }
}