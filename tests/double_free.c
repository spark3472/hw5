#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

int main(int argc, char** argv) {
    printf("Testing Double Free\n");

    if (Mem_Init(6000) == -1)
    {
        printf("initialization failed\n");
        exit(EXIT_FAILURE);
    }
    void* ptr = Mem_Alloc(8);
    printf("ptr location: %p\n", ptr);
    if (Mem_Free(ptr, 0) == -1)
    {
        printf("First free failed\n");
    }
    if (Mem_Free(ptr, 0) == 0)
    {
        printf("Double free error\n");
    }
  
}