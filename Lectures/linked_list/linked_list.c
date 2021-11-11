// idea of a linked list: size of c array is fixed, 
//however, in python you can insert and append elements. 
//you can do this with a linked list.

//append
//length
//max
//rec_length
//delete

#include<stdio.h>
#include<stdlib.h>

struct node {
    int data; //in python: void *data, and also the data type
    struct node *next;  //pointer to next piece of data

};

void append(struct node *head, int value){
    struct node *cur = head;    //taking the head value and making it the value of
    while(cur->next != NULL){
        cur = cur->next;
    }
    //cur->next is now equal to null
    struct node *node = (struct node *)malloc(sizeof(struct node));  //malloc returns an address. make me space in memory for my struct and 
    node->data = value; 
    node->next = NULL;
    cur->next = node;
};

int max_list(struct node *head){
    struct node *cur = head;
    int curmax = cur->data;
    while(cur != NULL){
        if(cur->data > curmax){
            curmax = cur->data;
        }
        cur = cur->next;
    }
    
    return curmax;

}


int main(void) {
    struct node *node0 = (struct node *)malloc(sizeof(struct node));  //malloc returns an address. make me space in memory for my struct and 
    node0->data = 3;

    struct node *node1 = (struct node *)malloc(sizeof(struct node));
    node1->next = node1;
    node1->data = 5;
    node1->next = NULL;


    printf("hi\n");
    return 0;
}

