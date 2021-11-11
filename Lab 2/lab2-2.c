#include "csc190_utils.h"

// 3. Implement a linked list (with print and append) that can store objects of
//    type int, float, and double. Use the following struct:

// struct node{
//     void *p_data; //a pointer to data (allocated with malloc)
//     int type; // 0 if int, 1 if float, 2 if double
//     struct node *next;
// };
  
//    You may like to write the functinos append_int, append_float, and append_double separately.

struct node 
{
    void *p_data; //a pointer to data (allocated with malloc)
    int type; // 0 if int, 1 if float, 2 if double
    struct node *next;
};

void print(struct node *head)
{
    while (head != NULL)
    {
        switch (head->type)
        {
            case 0:
                printf("%d ", *(int*)(head->p_data)); break;
            case 1:
                printf("%f ", *(float*)(head->p_data)); break;
            case 2:
                printf("%f ", *(double*)(head->p_data)); break;
        }
        head = head->next;
    }
    printf("\b\n");
}

int append_int(struct node *head, int value)
{   
    while(head->next != NULL)
        head = head->next;
    struct node *node = (struct node*)malloc(sizeof(struct node));  
    if (node == NULL)
        return 1;
    
    int *data = (int*)malloc(sizeof(int));
    *data = value;
    node->p_data = (void*)data;
    node->type = 0;
    node->next = NULL;
    head->next = node;
    return 0;
}

int append_float(struct node *head, float value)
{
    while(head->next != NULL)
        head = head->next;
    struct node *node = (struct node*)malloc(sizeof(struct node));  
    if (node == NULL)
        return 1;

    float *data = (float*)malloc(sizeof(float));
    *data = value;
    node->p_data = (void*)data;
    node->type = 1;
    node->next = NULL;
    head->next = node;
    return 0;
}

int append_double(struct node *head, double value)
{   
    while(head->next != NULL)
        head = head->next;
    struct node *node = (struct node*)malloc(sizeof(struct node));  
    if (node == NULL)
        return 1;
    
    double *data = (double*)malloc(sizeof(double));
    *data = value;
    node->p_data = (void*)data;
    node->type = 2;
    node->next = NULL;
    head->next = node;
    
    return 0;
}

void free_list(struct node *head)
{
    struct node* next;
    while(head != NULL)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

int main(int argc, char *argv[])
{
    struct node *node0 = (struct node*)malloc(sizeof(struct node));
    
    float f = 1.0f;
    node0->p_data = (void*)&f;
    node0->type = 1;
    append_double(node0, 5.0);
    append_float(node0, 2.3f);
    append_int(node0, 5);
    print(node0);
    free_list(node0);
    return 0;
}
