#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>

#define TRUE 0
#define FALSE 1

int m_error;

#define E_BAD_ARGS 0
#define E_NO_SPACE 1




//Header struct
//Using Dianna Xu's struct and block* functions
typedef struct _block {
    uint64_t footer; 
    uint32_t size; 
    uint16_t merge; 
    uint16_t free; 
    struct _block *prev; 
    struct _block *next;
} block;

int *last_address = 0;
uint32_t initial_size;


#define HS 2
static void *hide(block *this) 
{
    return (void *) ((uint64_t *)this+HS); 
}
static block *show(void *memory) 
{
    return (block *)((uint64_t *)memory-HS);
}

struct _block* head;
int ismem_init = 0;
int Mem_Init(long sizeOfRegion)
{
    
    if (ismem_init || sizeOfRegion <= 0)
    {
        m_error = E_BAD_ARGS;
        return -1;
    }else
    {
        ismem_init++;
    }

    
    
    sizeOfRegion += (sizeOfRegion/8+1) * 32 + 64;
    initial_size = sizeOfRegion;
    int pages = getpagesize();
    pages = pages/sizeOfRegion;

    
    void *new_region = mmap(last_address, sizeOfRegion, PROT_READ | PROT_WRITE,
                            MAP_ANONYMOUS | MAP_PRIVATE, -1, pages);
    if (new_region == MAP_FAILED) {
        return -1;
    }

    head = (struct _block*)new_region;
    head->footer = 0;
    head->size = sizeOfRegion;
    head->merge = 0;
    head->free = 1;
    head->prev = NULL;
    head->next = NULL;

    return 0;
}

block* find_free_block(long size)
{
    block* current = head;
    block* free = head;
    while(current != NULL)
    {
        if (current->size > size + 32 && free->size < current->size)
        {
            free = current;
        }
        current = current->next;
    }
    if (free->size > size + 32)
    {
        return free;
    }else
    {
        return NULL;
    }

}

void remove_from_free(void* ptr)
{
    block* allocated = show(ptr);
    allocated->free = 1;
    
    block* next = allocated->next;
    block* prev = allocated->prev;

    if (prev == NULL) {
        if (next == NULL) {
            head = NULL;
        } else {
            head = next;
            next->prev = NULL;
        }
    } else {
        if (next == NULL) {
            prev->next = NULL;
        } else {
            prev->next = next;
            next->prev = prev;
        }
    }

}

void *Mem_Alloc(long size)//Worst-Fit policy
{   
    int remainder = size%8;
    if (remainder != 0)
    {
        size += 8 - remainder;
    }

    block* to_return = find_free_block(size);
    if (to_return == NULL)
    {
        m_error = E_NO_SPACE;
        return NULL;
    }else
    {
        void* address = hide(to_return);
        to_return->free = 0;
        block* next = address + size;
        to_return->next = next;

        if(to_return->prev != NULL)
        {
            to_return->footer = to_return->prev->size;
        }
        next->merge = 0;
        next->free = 1;
        next->next = NULL;
        next->prev = to_return;
        initial_size = initial_size - size - 32;
        next->size = initial_size;
        to_return->next = next;
        head = next;
        if (address == NULL)
        {
            
            //set m_error to E_NO_SPACE
            return NULL;
        }
        return address;

    }

}

void add_to_free(void* ptr)
{
    block* freed = show(ptr);
    freed->free = 1;
    
    if(head != NULL)
    {
        freed->next = head;
        head->merge = 1;
        freed->prev = NULL;
        head->prev = freed;
        head = freed;
    }else{
        head = freed;
        freed->prev = NULL;
        freed->next = NULL;
    }

}

int Mem_Free(void *ptr, int coalesce)
{
    
    if (coalesce != 1 && coalesce != 2 && coalesce != 0)
    {
        return -1;
    }
    block* this = show(ptr);
        //if coalesce = 1
        
        if (coalesce == 1)
        {
            if(ptr != NULL)
            {
                add_to_free(ptr);
            }
            int again = 0;
            block* start = head;
            start = start->next;

            do {
                again = 0;

                if(start != NULL)
                {
				    if (start->free == 1 && start->merge == 1)
					{

						again = 1;
                        block* prev = start->prev;
                        
                        remove_from_free(hide(start));
                        
                        prev->size += (start->size - 30000);
                        start = start->prev;
						
					}
                }
                if (start->next == NULL)
                {
                    break;
                }else
                {
                    start = start->next;
                }

            } while (again);

            if (ptr == NULL)
            {
                return -1;
            }else
            {
                return 0;
            }

        }else if (coalesce == 2 && ptr != NULL)
        {

            if (ptr == NULL)
            {
                return -1;
            }else
            {
                if (this->free != 1)
                {
                    add_to_free(ptr);
                }else
                {
                    return -1;
                }
                
            }
            
            if (this->free == 1 && this->merge == 1)
            {
                block* prev = this->prev;
                remove_from_free(ptr);
                prev->size += this->size;
                this = this->prev;
            }

            return 0;
        }else if (coalesce == 0)
        {
            if (ptr == NULL)
            {
                return -1;
            }else
            {
                add_to_free(ptr);
            }
            return 0;
        }
    
    return -1;
}

void Mem_Dump()
{
    block* traverse = head;
    while(traverse != NULL)
    {
        printf("%p\n", traverse);
        traverse = traverse->next;
    }
}
                        
int main()
{
    Mem_Dump();
}
