#include "Q1.h"

#include <string.h>
#include <stdio.h>

int main(void)
{
    char s1[] = "aBCdeBCA";
    char s2[] = "BC";
    remove_str(s1, s2);
    printf("%d\n", strcmp(s1, "adeA"));
    return 0;
}