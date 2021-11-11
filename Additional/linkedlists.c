#include "csc190_utils.h"
#include "lab4.h"
#define DEBUG



void insert(struct Node *head, void *obj, size_t size)
{
    assert(head);
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->obj = obj;
    if (head->next)
    {
        newNode->next = head->next;
        head->next = newNode;
    }
    else 
    {
        newNode->next = NULL;
        head->next = newNode;
    }
}

int compare (const void *A, const void *B, size_t size)
{
    for (uint i = 0; i < size; ++i)
    {
        if(((char*)A)[i]!=((char*)B)[i])
            return 0;
    }
    return 1;
}

void deleteNode(struct Node **head, const void *val, size_t size)
{
    struct Node *prev = *head;
    struct Node *temp = NULL;
    while (prev)
    {
        if(compare(prev->obj, val, size))
        {
            if (prev==*head)
            {
                *head = prev->next;
                // free(prev->obj);
                free(prev);
                return;
            }
            temp->next = prev->next;
            // free(prev->obj);
            free(prev);
        }
        temp = prev;
        prev = prev->next;
    }
}

void freeList(struct Node *head)
{
    struct Node *temp;
    while (head)
    {
        #ifdef DEBUG
        printlong(head);
        printlong(head->obj);
        #endif
        free(head->obj);
        temp = head;
        head = head->next;

        #ifdef DEBUG
        printstr("obj freed");
        #endif

        free(temp);

        #ifdef DEBUG
        printstr("head freed");
        #endif
    }
}