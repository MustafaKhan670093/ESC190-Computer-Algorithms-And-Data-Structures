#include "csc190_utils.h"
#include "lab4.h"

int main(int argc, char **argv)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    void *obj1 = malloc(20), *obj2 = malloc(30);
    memset(obj1, 10, 20);
    printlong(obj1);
    printlong(obj2);
    insert(node, obj1, 20);
    insert(node, obj2, 30);
    printlong(node);
    deleteNode(&node, obj1, 20);
    printlong(node);
    freeList(node);
    return 0;
}