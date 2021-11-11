#include "Q2.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct node *n1 = (struct node *)malloc(sizeof(struct node));
    struct node *n2 = (struct node *)malloc(sizeof(struct node));
    struct node *n3 = (struct node *)malloc(sizeof(struct node));
    struct node *n4 = (struct node *)malloc(sizeof(struct node));

    n1->value = 1;
    n1->next = n2;
    n2->value = 2;
    n2->next = n3;
    n3->value = 2;
    n3->next = n4;
    n4->value = 3;
    n4->next = NULL;

    printf("%d\n", count_links(n1)); // 0

}