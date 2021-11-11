#include "csc190_utils.h"

// 1. For a linked list struct defined as below, write a function that prints out all 
//    the data in the linked list. Do not use recursion.

// struct node{
//     int data; 
//     struct node *next; 
// };

// 2. Same as (1), but now use recursion.

typedef struct node
{
    int data;
    struct node *next;
} node;

void print(node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void print_recursion(node *head)
{
    if (head==NULL)
        printf("\n");
    printf("%d ", head->data);
    print_recursion(head->next);
}

int main(int argc, char* argv[])
{
    node *n1, *n2, *n3;
    n1 = (node*)malloc(sizeof(node));
    n2 = (node*)malloc(sizeof(node));
    n3 = (node*)malloc(sizeof(node));
    n1->data = 1;
    n2->data = 2;
    n3->data = 3;
    n1->next = n3;
    n2->next = NULL;
    n3->next = n2;
    print(n1);
}


