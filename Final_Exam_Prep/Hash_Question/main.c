/*

Given an array of integers nums and an integer target, 
return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, 
and you may not use the same element twice.

You can return the answer in any order.

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].

Constraints:

2 <= nums.length <= 103
-109 <= nums[i] <= 109
-109 <= target <= 109

*/

#include "hashtable.h"
#include <stdio.h>

int hash_fn(int key, int table_size){
    return key % table_size;
}

int probe_fun(int i, int key){
    return i*i;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    // make hash function
    *returnSize = 2;
    struct hashtable *ht;
    ht_create(&ht, 0.8, hash_fn, probe_fun);
    for (int i = 0; i < numsSize; ++i) {
        ht_set(ht, nums[i], i);
    }

    for (int i = 0; i < numsSize; ++i) {
        // is target - nums[i] in the hash table?
        if (ht_in(ht, target - nums[i])){
            int *out = (int *)malloc(sizeof(int)*2);
            out[0] = i;
            out[1] = ht_get(ht, target - nums[i]);
            return out;
        }
    }
}


/*

int B = 1009;

struct node{

    int key;
    int index;
    struct node *next;

};

struct hash_node{

    int occupied;

    struct node *first;
    struct node *last;

};

struct hash_node a[1009];

void init_list()
{
    memset(a, 0, sizeof(struct hash_node)*B);
}

int hash_func(int key)
{

     if(key<0)
         key*=-1;

     return key%B;
}


void insert(int key, int index)
{
    int hash_entry = hash_func(key);

    struct node *p = (struct node*)malloc(sizeof(struct node));

    if(a[hash_entry].occupied==0)
    {
        p->key = key;
        p->index = index;
        p->next = NULL;
        a[hash_entry].first = p;
        a[hash_entry].last = p;
        a[hash_entry].occupied = 1;
    }
    else
    {
        a[hash_entry].last->next = p;
        p->next = NULL;
        a[hash_entry].last = p;
    }

}

int find(int key)
{
    int hash_entry = hash_func(key);


    if(a[hash_entry].occupied == 0)
        return -1;

    struct node *p = a[hash_entry].first;

    while(p!=NULL)
    {

        if(p->key == key)
            {
             
                return p->index;
            }
        p = p->next;
    }

    return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
      
      init_list();
    
     *returnSize=2;
      int *res = (int*)malloc((*returnSize)*sizeof(int));
    
    
    for(int i=0; i<numsSize; i++)
    {
       int cur = nums[i];

     
            int index = find(target-cur);
            if(index>=0)
            {
                res[0] = index;
                res[1] = i;
                break;
            }
        
        insert(nums[i], i);
    }
    return res;
}
*/