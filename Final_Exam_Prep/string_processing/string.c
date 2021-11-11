/************************************************
String-processing using iteration and recursion:
- strlen
- strcpy
- strcat
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************
iterative strlen() function
***************************/
int my_strlen(char *s1){
    int len = 0;
    //Note: '\0' is the NULL character for strings
    while(*s1 != '\0'){
        len ++; //this is simply len = len + 1 in C
        s1++; //this moves to the next character in the string
    }
    return len;
}

/**************************
recursive strlen() function
***************************/
int recursive_strlen(char *str)
{
    static int length=0;
    if(*str!=NULL){
        length++;
        stringLength(++str);
    }
    else{
        return length;
    }
}

/**************************
iterative strcpy() function
***************************/
int my_strcpy(char *dest, char *src){
    while(*src != '\0'){
        *dest = *src;
        src++;
        dest++;
    }
    *dest = *src;
}


/****************************
another implmenetation of the
iterative strcpy() function
*****************************/
void my_strcpy2(char *dest, char *src){
    while(*src != '\0')
        *dest++ = *src++; //equivalent to *dest = *src; dest++; src++;

    *dest = *src;      
    //*++dest = *++src; // equivalent to dest++; src++; *dest = *src; 
}


/**************************
recursive strcpy() function
***************************/
void recursive_strcopy(char *s1, char *s2){
  // if not at end of s2
  if(*s2) { 
    *s1++ = *s2++;
    strcopy(s1, s2);
  }
  //terminate the string with a null character
  else *s1 = '\0'; 
}


/**************************
iterative strcat() function
***************************/

//Note: strcat() appends a copy of the given string to another string.

char* my_strcat(char* destination, const char* source)
{
    // make ptr point to the end of destination string
    char* ptr = destination + strlen(destination);
 
    // Appends characters of source to the destination string
    while (*source != '\0')
        *ptr++ = *source++;
 
    // null terminate destination string
    *ptr = '\0';
 
    // destination is returned by standard strcat()
    return destination;
}

/**************************
recursive strcat() function
***************************/
void recursive_strcat(char *dest, char *src){
    if (*dest != '\0') {
    my_strcat(++dest, src);
    } else {
    if ((*dest = *src) != '\0') {
        my_strcat(++ dest, ++ src);
    } else {
        return; 
    }
    }
}

/**************************************
recursive strcat() function in one line
***************************************/
void my_strcat(char *dest, char *src)
{
  (*dest)? my_strcat(++dest, src): (*dest++ = *src++)? my_strcat(dest, src): 0 ;
}


int main(void)
{
    
    char c1 = 'a';
    char c2 = 'A';
    char *s1 =  "asdfjasdfj";
    // s1[2];
    // s1[2] = 'z';
    char *s2 = (char *)malloc(sizeof(char) * 20);
    s2[0] = 'A';
    char s3[20];

    // "abc"  C stores: ['a', 'b', 'c', '\0']
    char s4[4] = "ab";
    printf("%s\n", s4);  //s4[0] s4[1] s4[2] ,
    printf("%c\n", *s4);

    // copy string
    char s5[20] = "abc";
    char s6[20];
    strcpy(s6, s5); //s6 is destination, s5 is source
    //s6 = s5 is an error
    strlen(s5); //the length of s5 (num of characters, not counting '\0')
    strcmp(s5, s6); // <0 s5 comes before s6 in lexigroaphic ordering
                    //0 if s5 and a6 are the same
                    // >0 otherwise
    //not the same as s5 == s6 (for pointers, checks whether s5 and s6 are aliases)

    char *a = (char *)malloc(sizeof(char)*50);
    strcpy(a, "abcdefg");
    char *b = a;
    //b[2] = 'z' => a[2] is also 'z'

    return 0;
}