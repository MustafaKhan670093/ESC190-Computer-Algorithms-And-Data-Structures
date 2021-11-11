#include "csc190_utils.h"

// Lab 1
// =====

// 1. In your main function, define the variable int a and initialize it to 5.
//    Now, write a function which does not return anything, but can set the value of 
//    an integer to 10.
   
//    Use this function to set the value of a to 10.
   
//    Use printf to demonstrate that the value of a changed.
   
//    Now, put a breakpoint at int a = 5, and trace the code.

// 2. Implement a function that performs Insertion Sort https://en.wikipedia.org/wiki/Insertion_sort#Algorithm
//    The function should take in an array of integers, and modify the array so that it's 
//    sorted in increasing order.
  
//    Here is code to print out an array of integers using a for-loop and a while-loop in C.

//    int i = 0;
//    int a[5] = {2, 3, 4, 5, 6};
//    // initialize i to 0, run the loop while i < 5, and increase i by 1 every time;
//    // Here, i++ is the same as i = i + 1
//    for(i = 0; i < 5; i++){
//        printf("%d\n", a[i]);
//    }

//    i = 0;
//    while(i < 5){
//        printf("%d\n", a[i]);
//        i++; // same as i = i + 1
//    }

//you declare globals here like at the top...

void sort(int *arr, size_t size)
{
    size_t i = 1;
    while (i < size)
    {
        size_t j = i;
        while (j > 0 && arr[j-1]>arr[j])
        {
            int temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            --j; 
        }
        ++i;
    }
}



// Q.1 

void return_10(int *a) {
    *a = 10;
}

int main(int argc, char **argv) 
{
    int a;
    a = 5;
    return_10(&a);
    printf("%d\n", a);

    int *c = (int*)malloc(10000000*sizeof(int));
    for (size_t i = 0; i < 10; ++i)
    {
        c[i]=-i;
    }
    sort(c,10);
    for (size_t i = 0; i < 10; ++i)
    {
        printf("%d ", c[i]);
    }
}