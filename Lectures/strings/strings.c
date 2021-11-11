#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strlen(char *s1) {
    //test: s1 = ['a', 'NULL']
    int len = 0;
    while(*s1 != NULL) { //Note: Use '\0' as an equivalent to null. otherwise, ignore the error.
        len++; // same as len += 1;
        s1++;  // means make *s1 be the address of the second character;
    }
    return len;
}

void my_strcpy(char *dest, char *src) {
    while(*src != NULL){
        *dest = *src;
        src++;
        dest++;
    }
    *dest = *src;
}

/* An alternative way of writing it
void my_strcpy(char *dest, char *src) {
    while(src != NULL){
        *dest++ = *src++; //equivalent to *dest = *src; dest++; src++; 
    }
    *++dest = *++src; //equivalent to dest++; src++; *dest = *src
}
*/

int main(void) {
    char c1 = 'a';
    char c2 = 'A'; 
    char *s1 = "asdfghjk"; //this is a string literal
    //access individual elements using s1[2] for example
    //note however, s1[4] = 'z'; might work but not usually
    //this is because c might not put it in an area of memory that is changeable
    char *s2 = (char *)malloc(sizeof(char) * 20);
    s2[0] = 'A';
    char s3[20]; //an array of chars of size 20

    // "abc", c stores ['a', 'b', 'c', 'NULL'] //a string is a pointer to a char
    char s4[4] = "abs";
    printf("%s\n", s4);
    printf("%c\n", *s4);

    //copy one string to another
    char s5[20] = "abc";
    char s6[20];
    strcpy(s6, s5); //first param is destination, second param is source. it copies s5 to s6. 
    //note: we cannot say s6 = s5 as we cannot reassign an array. even if it was possible, it would just make s6 an alias, and not a copy.

    //length of string
    strlen(s5); //the length of s5 (number of characters not counting NULL)

    //
    strcmp(s5, s6); // returns value < 0 if s5 comes before s6 in lexigroaphic ordering
                   // returns 0 if s5 and s6 are the same
                   // > 0 otherwise
                   // Note: This is not the same as s5 == s6 (for pointers, checks whether s5 and s6 are aliases)

    my_strlen("what's up?");
    
    return 0;
}