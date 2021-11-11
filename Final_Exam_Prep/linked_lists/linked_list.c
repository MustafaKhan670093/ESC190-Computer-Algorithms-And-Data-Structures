/***************************************************** 
Algorithms for managing a linked list: 
- Insertion (iteratively and recursively)
- Deletion/Freeing_list (iteratively and recursively)
- Finding max value 
- Finding min value 
- Delete a specific node given a 
  reference (pointer to a pointer) and a key
******************************************************/

#include <stdio.h>
#include <stdlib.h>

/***********************
Defining the node struct
************************/
struct node {
    int data;
    struct node *next;
};

/*************************************
Insert iteratively using a while loop
**************************************/
void insert_iter(struct node *head, int value){
    struct node *cur = head; //taking the head value and making it the value of
    while(cur->next != NULL){
        cur = cur->next;
    }
    //cur->next is now equal to null, we have reached the end of the list 
    //and can begin inserting value
    struct node *node = (struct node *)malloc(sizeof(struct node)); //malloc returns an address
    node->data = value;
    node->next = NULL;
    cur->next = node;
};

/***************************************
Insert into linked list done recursively
****************************************/
struct node * insert_recur(struct node *head, int value){
    //if linked list is empty/we have reached the end of the list
    //insert new node.
    if(head == NULL){
        struct node *node = (struct node *)malloc(sizeof(struct node)); //malloc returns an address
        node->data = value;
        node->next = NULL;
        head = node;
        printf("7\n");
    }
    //If we have not reached the end of the linked list,
    //keep traversing it recursively.
    else{
        head->next = insert_recur(head->next, value);
    }
    return head;
}

/************************************
Helper function returns max of 2 ints
*************************************/
int max(int a, int b){
    if (a > b){
        return a;
    } else{
        return b;
    }
}

/************************************
Helper function returns min of 2 ints
*************************************/
int min(int a, int b){
    if (a < b){
        return a;
    } else{
        return b;
    }
}

/*************************************************
Returns the max value in a linked list recursively
**************************************************/
int max_list_rec(struct node *head){
    if(head->next == NULL){
        return head->data;
    }else{
        return max(head->data, max_list_rec(head->next));
    }
}

/*************************************************
Returns the min value in a linked list recursively
**************************************************/
int min_list_rec(struct node *head){
    if(head->next == NULL){
        return head->data;
    }else{
        return min(head->data, min_list_rec(head->next));
    }
}

/**********************************************
Returns the length of a linked list recursively
***********************************************/
int list_len_rec(struct node *head){
    if(head == NULL){
        return 0;
    }else{
        return 1 + list_len_rec(head->next);
    }
}

/***************************************************
Iteratively frees nodes in a linked list from memory 
****************************************************/
void free_list(struct node *head){
    struct node *next = NULL;
    while(head != NULL){
        next = head->next;
        free(head);
        head = next;
    }
}

/***************************************************
Recursively frees nodes in a linked list from memory 
****************************************************/
void free_list_rec(struct node *head){
    if(head == NULL){
        return;
    }else{
        free_list_rec(head->next);
        free(head);
    }
}

/*************************************************
Delete specific nodes in a linked list from memory 
**************************************************/

/* Given a reference (pointer to pointer) to the head of a
   list and a key, deletes the first occurrence of key in
   linked list iteratively */ 
void deleteNode(struct node** head_ref, int key)
{
    // Store head node
    struct node *temp = *head_ref, *prev;
 
    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
 
    // If key was not present in linked list
    if (temp == NULL)
        return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 
    free(temp); // Free memory
}



int main(void){
    struct node *node0 = (struct node *)malloc(sizeof(struct node));
    node0->data = 3;
    struct node *node1 = (struct node *)malloc(sizeof(struct node));
    node0->next = node1;
    node1->data = 5;
    node1->next = NULL;
    insert_iter(node0, 6);
    insert_recur(node0, 7);
    free(node0);
    free(node1);
    return 0;
}