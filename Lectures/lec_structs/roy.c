#include <stdio.h>
#include <stdlib.h>

int* makearr(int size_arr);

struct student_record
{
    int esc180_mark;
    int phy180_mark;
};


int main(void)
{
    struct student_record s;
    struct student_record s2;
    
    s.esc180_mark = 20;

    printf("%ld, %ldi, %ld \n", (long int)&s, (long int)(&s.esc180_mark), (long int)(&s.phy180_mark)); //getting rid of the warning with castings

    int* a = (int*)malloc(10 * sizeof(int));

    int* c = makearr(10);
    c[10] = 10;
    printf("%i", c[10]);
    free(c);
    return 0;
}

int* makearr(int size_arr)
{
    return (int*)malloc(size_arr * sizeof(int));
}