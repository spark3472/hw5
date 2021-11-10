

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include <unistd.h>

int main()
{
    printf("Allocing until no more space\n");
    if(Mem_Init(6000) == -1)
    {
        printf("Initialization failed\n");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    int count2 = 0;
    while(1)
    {
        void* ptr = Mem_Alloc(8);
        count++;
        
        if (ptr == NULL)
        {
            printf("Number of Allocs: %d\n", count);
            printf("%d NO SPACE\n", m_error);
            exit(EXIT_SUCCESS);
        }
    }
    
}