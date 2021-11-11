#include "Q2.h"
#include <stdio.h>
#include <stdlib.h>

/*
The following struct is used to store the frequency of 
occurence of different integers in a linked list.
*/
struct node_occur
{
    int num;
    int frequency;
    struct node_occur *next;
};


/*
This function traverses the linked list once and 
adds the frequency of different numbers to the struct
created above.
*/
void occur(struct node *head, struct node_occur **result)
{
    struct node *p;
    struct node_occur *temp, *prev;
 
    p = head;
    while (p != NULL)
    {
        temp = *result;
        while (temp != NULL && temp->num != p->value)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)
        {
            temp = (struct node_occur *)malloc(sizeof(struct node_occur));
            temp->num = p->value;
            temp->frequency = 1;
            temp->next = NULL;
            if (*result != NULL)
            {
                prev->next = temp;
            }
            else
            {
                *result = temp;
            }
        }
        else
        {
            temp->frequency += 1;
        }
        p = p->next;
    }
}
 
/*
Display function used in debugging. Uncomment this
and the disp_occur(head) line in the count_links function
in order to use it.
*/

// void disp_occur(struct node_occur *p)
// {
//     printf("***************************\n  Number\tOccurence\n***************************\n");
//     while (p != NULL)
//     {
//         printf("    %d\t\t%d\n", p->num, p->frequency);
//         p = p->next;
//     }
// }

/*
This was the function we were tasked with constructing.
After initializing a pointer to the head of the linked list 
given in the question as well as initializing a NULL head
for the occur() function to store frequency of the numbers
in the first linked list, we compare whether the number == 
the frequency to determine whether we return 1 or 0.
*/
int count_links(struct node *node){
    struct node* current = node;
    struct node_occur *head = NULL;
    occur(current, &head);
    int count = 0;
    //disp_occur(head);
    while (current != NULL) {
        if (current->value != head->frequency)
            return 0;
        count++;
        current = current->next;
        head = head->next;
    }
    return count; 
}

/*
Justification about why this runs in O(M+N)

A simple example of somehting that runs in O(M+N) is:
 
int sum(int[] nArr, int[] mArr) {
    int sum = 0;
    for(int i : nArr) {
        sum += i;
    }
    for(int i : mArr) {
        sum += i;
    }
    return sum;
}

Much like this algorithm, my program iterates through M elements of the linked list
in order to determine the frequency of the numbers there.

Then, the count_links program iterates through the N elements of this new node_occur linked list
in order to determine if the number and the occurence of the number are the same.

As per the question, we assume that malloc takes O(1) time and all other operations such as conditional
checks are assumed to also take O(1) time. Therefore, this program runs in O(M+N) time as required.
*/