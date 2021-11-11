#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 
1. a. What are the three steps that convert a C program into executable code. 
Which function in the C program does execution begin from? 

Pre-processing (modifies original program), compiling (converts to machine code) and
linking (combines additional libraries if necessary). Execution starts from the main
function.

1. b. Will this function definition result in any accidental loss of 
information and if so why? If not, why not?

float f(char a, float b)
{
short int d=a;
return b+d;
}

There will be no undefined behaviour as short int uses more bits than char to store
a value and char can be treated as numbers as integers occupying 8 bits. In the return
statement, d is type cast into float and this value is added with b which is a float. Hence,
no information is lost.

1. c. Re-write the following function so that the same behaviour of f is retained but with only one if statement
and without any else statements (i.e. replace the following four if statement blocks and the else block
with one if statement).

void f(int a){
    if (a<3)
    {
        if(a>=-1){
        printf("%d\n",a);
        }
        if(a < -2){
            printf("%d\n",a);
            }
        if(a<-1 && a>=-2){
            printf("%d\n",a+1);
            }
    } else {
        printf("%d\n",a+1);
        }
}
*/

float division(float a){
    if(a==1.0){
        return a;
    } else {
        division(a/2);
    }
    }



void f(int a){
    if(a<3 && (a>-1) || (a<-2)){
       printf("%d\n",a); 
       return;
    }
    printf("%d\n",a+1);
    }

//Fibonacci numbers
int fib(int n){
    if (n==0) {
        return 0;
        }
    else if(n==1){
        return 1;
    }
    return fib(n-1)+fib(n-2);
    }

int sumFib(int n, int s){
    if (n<1) {
        return 0;
    }
    else if (n==1){
        return 1;
    }
    if(s==0){
        return sumFib(n-1,0)+sumFib(n-2,0);
    }
    else{
        return sumFib(n-1,1)+sumFib(n,0);
    }
}


int sumFib1(int n, int s){
    int sum=0;
    if(n<1){
        return 0;
    }
    else if(n==1){
        return 1;
    }
    if(s!=0){
        while(n>0){
            sum = sum + sumFib1(n,0);
            n=n-1;
        }
        return sum;
    }
    return sumFib1(n-1,0)+sumFib1(n-2,0);
}

/*
Q.2 2015 Midterm 
Implement the function void initArray(int ** a, int n) which dynamically 
allocates an array of size n for storing n integer elements. 
Each element in the array should be set to 0.
*/
void initArray(int **a, int n){
    int i;
    int *array = (int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        array[i] = 0;
    }
    *a=array;
}



/*
Q.3 2016 Midterm Term 2
Implement the void pop(struct Stack * s, struct Data * d) operation that can be performed on a
stack using only queues. The Stack structure is defined as follows:
*/
struct Stack{
    struct Queue * q1;
    struct Queue * q2;
    int count;
};

struct Data{
int data;
};

void enqueue(struct Queue * q, struct Data d);
void dequeue(struct Queue * q, struct Data * d);
int isEmpty(struct Queue * q);

void pop(struct Stack * s, struct Data * d){
    struct Queue *tempQ; //create a temporary queue
    int numNodes=s->count; //retrieves count in s (which is a Stack)
    if(s->count!=0){
        while(numNodes>1){
            dequeue(s->q1, d);
            enqueue(s->q2, *d);
            numNodes = numNodes - 1;
        }
        dequeue(s->q1, d);
        tempQ=s->q1;
        s->q1=s->q2;
        s->q2=tempQ;
        s->count--;
    }
    else{
        (*d).data=-1;
    }
}



/*
Q.4 2016 Midterm Term 2
int findLargestSum(int * array, int n, int * a, int *b) which computes 
the largest sum of a set of continuous elements in the array.
For instance, suppose the array {−2, −3, 4, −1, −2, 1, 5, −3} is passed to the
function findLargestSum. The sub-array in this array containing the largest sum is { 4, −1, −2, 1, 5}
which begins from index 2 and ends at index 6 of the original array. 
*/

int findLargestSum(int * array, int n, int * a, int *b)


int main(){

    /*Q. 1. d. Rewrite:
    i=n;
    do{
    printf("%d\n",i);
    i=i+1;
    }while(i<n);
    
    Solution:
    int i;
    for(i=n; i<n; i++){
        printf("%d\n",i);
    }

    1. e. Assume that in the initial function call to division, a>1. 
    Do you foresee any possible issues with this code? If so and 
    if not, why? Are there other restrictions on the possible values a can take?

    */



    // printf("%f", division(8.0));

    // int *a, b=1, c;
    // a=&b;
    // //*&**&a;
    printf("%d\n", sumFib1(6, 1)); //Note: s has to be non zero
    printf("%d\n", sumFib(6, 1));
    return 0;
}