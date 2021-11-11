#include <stdio.h>
#include <stdlib.h>

// void means nothing. it implies the function doesn't return anything
void f(int a)
{
    printf(2*a);
}

int main()

    int a = 8; //other types include

    /*multi
    line
    comment*/



    printf("2*a = %d", 2*a); //%d: decimal (int)
                             //%s: string
                             //$ld:long (long int)


    int grade = 97;
    if(grade >= 50){
        printf("pass\n");
    }
    else if(grade >= 85){
        printf("excellent\n");
    }
    else {
        printf("seems like you need to work\n");
    }

    //Type: Pointer
    int *p_a = &a; //* (star) indicates pointer and &a means address of a

    printf("%ld\n", p_a); //p_a: the address of a
    printf("%ld\n", *p_a); //*p_a: the value at the address of a


    return 0;
}
