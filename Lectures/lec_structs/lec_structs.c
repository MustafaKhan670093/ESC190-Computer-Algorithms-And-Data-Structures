#include <stdio.h>
#include <stdlib.h>

// #include <stdlib.h> is where malloc is defined

struct student_record{
    int esc180;
    int phy180;
};

//no effect
void f0(int a){
    a = 100; 
}

//has no effect to change the value of esc180
void f(struct student_record s){
    s.esc180 = 100;
}


//change value of esc180 by changng value at addresses
void f1(int *a){
    *a = 100;
}

// function taking address of student_record
void f2(struct student_record *ps){
    (*ps).esc180 = 100; //has an effect. Goes to address, finds esc180 and changes value
    //Note: brackets are there for precedence. 
}

//has an effect
void f3(struct student_record *ps){
    // Note: (*a).b is equivalent to a->b but only works if a is a pointer
    ps->esc180 = 100;
}

//function to make an array of a particular size (maloc + the heap, self study more)
int *make_arr(int size_arr){
    return (int *)malloc(size_arr *sizeof(int));
}

//why can't you use this?
int *make_arr10_wrong(){
    int a[10]; //local variable
    return a;
    //note: this is a local variable. memory gets redumped and value can be changed.
    //that's why this array though it might work but we can't rely on a local variable being 
    //there after a function is done. On the contrary, a variable/data type defined using malloc will stay
    //on the heap until specified otherwise.
}

//NOTE: Stack is where memory lives. Heap is where memory allocated by malloc lives.

//why can't you use this?
int *make_int_wrong(){
    int a; //local variable
    return a;
    //note: this is a local variable. memory gets redumped and value can be changed.
    //that's why this array though it might work but we can't rely on a local variable being 
    //there after a function is done. On the contrary, a variable/data type defined using malloc will stay
    //on the heap until specified otherwise.
}

int main(void){
    struct student_record s;
    struct student_record s1;
    s.esc180 = 94;
    s1.esc180 = 95;
    f(s);
    f1(&s.esc180); // this will have an effect
    f2(&s);

    //int a = 5;
    //float b = (float)a;

    printf("%ld %ld %ld", (long int)&s, (long int)&s.esc180, (long int)&s.phy180);

    int size_arr = 10;
    int *a = (int *)malloc(size_arr * sizeof(int));
    //malloc returns a variable of type void* (a pointer but a pointer of no particular type), which we then cast
    a[5] = 15; // same as *(a + 5) = 15

    int *c = make_arr(50);
    c[10] = 40;
    free(c);

}