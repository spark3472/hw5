#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

int main()
{
    if (Mem_Init(6000) == -1)
    {
        printf("INITIALIZATION FAILED\n");
        exit(EXIT_FAILURE);
    }
    int* ptr = (int*)Mem_Alloc(sizeof(int)*3);
    int* pointer = (int*)Mem_Alloc(sizeof(int)*3);
    if (pointer == NULL)
    {
        printf("pointer null\n");
    }
    if (ptr == NULL)
    {
        printf("ptr null\n");
    }

    printf("Freeing but not coalescing...\n");
    Mem_Free(ptr, 0);
    Mem_Free(pointer, 0);
    Mem_Dump();

    printf("\n");

    printf("Coalescing...\n");
    Mem_Free(NULL, 1);
    Mem_Dump();
}