

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include <unistd.h>

#define half 300

int main()
{
    printf("Checking 8-byte alignment\n");
    if(Mem_Init(6000) == -1)
    {
        printf("Initialization failed\n");
        exit(EXIT_FAILURE);
    }
    int count = half;
    int count2 = 0;
    while(count > 0)
    {
        void* ptr = Mem_Alloc(8);
        count--;
        
        if (ptr == NULL)
        {
            printf("Number of Allocs: %d\n", count);
            printf("%d NO SPACE\n", m_error);
            exit(EXIT_FAILURE);
            break;
        }
    }

    while(1)
    {
        void* ptr = Mem_Alloc(1);
        count2++;
        if (ptr == NULL){
            printf("Number of Allocs: %d\n", half+count2);
            if (half + count2 != 753)
            {
                printf("not 8-byte aligned\n");
                exit(EXIT_FAILURE);
            }
            printf("%d NO SPACE\n", m_error);
            exit(EXIT_SUCCESS);
        }
    }
    
}