/******************************************************************************
 *  Types and Constants.                                                      *
 ******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bag.h"


    /* FUNCTION bag_print -- "hidden" function in avl_bag.c for debugging. */
extern // not strictly necessary -- it's the default for function
void bag_print(const bag_t *bag, int indent, void (*print)(bag_elem_t));

static
int float_cmp(bag_elem_t a, bag_elem_t b)
{
    return *(float *) a < *(float *) b ? -1
         : *(float *) a > *(float *) b; /* ? 1 : 0 would be redundant */
}

static void print(bag_elem_t a)
{
    printf("%.1f", *(float*)a);
}

int main (int argc, char* argv[])
{   
    size_t i;
    float elts[] = {3.2, 3.1, 3, 10, 11, 4, 1, 0, 0.2, 5, 0.4, 2};
    float bad_elts[] = {56, 0.001, 0.2000001, 75, 50, -1, 0.1};
    
    /* Create a new bag. */
    bag_t *b1 = bag_create(float_cmp), *b2 = bag_create(float_cmp);

    //This should be an AVL tree
    bag_insert(b1, (void*)elts);
    bag_insert(b1, (void*)(elts+1));
    bag_insert(b1, (void*)(elts+2));
    bag_insert(b1, (void*)(elts+3));
    bag_insert(b1, (void*)(elts+4));
    bag_insert(b1, (void*)(elts+5));
    bag_insert(b1, (void*)(elts+6));
    bag_insert(b1, (void*)(elts+7));

    //This should not be an AVL tree
    bag_insert_norot(b2, (void*)(elts+3));
    bag_insert_norot(b2, (void*)elts);
    bag_insert_norot(b2, (void*)(elts+1));
    bag_insert_norot(b2, (void*)(elts+2));

    //If we have successfully made both functions, there should be no error.
    assert(is_avl_tree(b1) && !is_avl_tree(b2));
    bag_print(b1, 6, print);

    printf("Now we'll remove a node from the tree: \n\n");

    avl_remove2(&(b1->root), (void*)(elts+2), float_cmp);
    avl_remove2(&(b1->root), (void*)(elts), float_cmp);
    // avl_remove2(&(b1->root), (void*)(elts+7), float_cmp);
    // avl_remove2(&(b1->root), (void*)(elts+6), float_cmp);
    // avl_remove2(&(b1->root), (void*)(elts+4), float_cmp);
    bag_print(b1, 6, print);
    
    
    bag_destroy(b1);
    bag_destroy(b2);    
}