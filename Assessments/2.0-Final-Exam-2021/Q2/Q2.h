#if(!defined(Q2_H))
#define Q2_H

struct node{
    struct node *next;
    int value;
};

int count_links(struct node *node);

#endif