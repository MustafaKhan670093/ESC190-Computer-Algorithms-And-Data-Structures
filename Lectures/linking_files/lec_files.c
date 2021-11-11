#include <stdio.h>
#include <stdlib.h>
#include "lec_files.h"

#define COURSE 180 //Any occurance of course will be substitued with 180. A constant defined at the beginning of the program. Convention, done in caps.
//Defining macros:
#define ABS(x) if(x < 0) - x else x


int f(void);

int main(void){
    f();
    printf("%d\n", COURSE);
    return 0;
}

int f(void)

