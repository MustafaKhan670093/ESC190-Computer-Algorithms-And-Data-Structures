#pragma once
#include "csc190_utils.h"

struct Node 
{
    void *obj;
    size_t size;
    struct Node *next;
};

void insert(struct Node *head, void *obj, size_t size);
void deleteNode(struct Node **head, const void *val, size_t size);
void freeList(struct Node *head);
