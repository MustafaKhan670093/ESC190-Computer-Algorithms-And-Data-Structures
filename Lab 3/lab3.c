#include "csc190_utils.h"
#include "lab4.h"

//Q.1
char *my_stringcat(const char *dest, const char *src)
{
    char *string = (char*)malloc((strlen(dest)+strlen(src)+1)*sizeof(char));
    // memcpy(string, dest, strlen(dest)*sizeof(char));
    // memcpy(string+strlen(dest), src, strlen(src)*sizeof(char));
    strcpy(string, dest);
    strcpy(string+strlen(dest), src);
    return string;
}


char *my_strcat(char *dest, const char *src)
{
    size_t d_len=0, s_len=0;
    while(dest[d_len])
        ++d_len;
    while(src[s_len])
        ++s_len;
    dest = (char*)realloc((void*)dest,(1+d_len+s_len)*sizeof(char));
    if (dest == NULL)
    {
        free(dest);
        return NULL;
    }
    memcpy(dest+d_len, src, (s_len+1)*sizeof(char));
    return dest;
}
/*
dest = "the", src = "cat"

string -> 0

012345
l5:
string = "012345"
l6:
copies "the" and replacs "012" = 0, 0+1, 0+2; string->t
string+3 ->3
copy "cat" to "345"; string = "thecat"
*/

//Q.2

int my_strcmp_rec(const char *str1, const char *str2)
{
    if (*str1=='\0' && *str2=='\0')
        return 0;
    return *str1 != *str2 ? *str1 - *str2 : my_strcmp_rec(str1+1, str2+1);
}

//Q. 3

// 3. The C library function atoi converts a string to an integer. Write
//    your own version of the function, with the signature
//    int atoi(char *str)
//    Hints:
//    * The function isdigit (defined in <ctype.h>) can be used to tell if 
//    a character is a digit
//    * You can convert a digit c to an integer value using c-'0'

int atoi(const char *str)
{
    int out = 0;
    while (*str!='\0')
    {
        if (isdigit(*str))
        {
            out = (out<<3)+(out<<1);
            out += *str -'0';
        }
        str++;
    }
    return out;
}

// 000.....000 << shift decimal point to the right 
// * sign: 0 for + 1 for -
// out = x
// x*10 = x*8 + x*2
//      = x*2^3+ x*2^1
// 3425312.4

// out = 23 '2'
// out = 10111.00000000000
// multiply by 10
// 23*8+23*3

// 000000000000010.000

// 000000000000010000.
//   0000000000000100.00
// 000000000000010100.00


// 000000000000010100.00
//                 11
// 000000000000010111.00

// x(0)
// y = ++x - 10
// x = x+1
// y = x - 10 -> y=-9

struct node
{
    struct node *next;
};

int floyd(struct node *head)
{
    struct node *turtle = head, *hare = head;
    do
    {
        if (turtle->next==NULL||hare->next==NULL||hare->next->next==NULL)
            return 0;
        turtle=turtle->next;
        hare = hare->next->next;
    } while (turtle != hare);
    return 1;
}


int main(int argc, char *argv[])
{
    char *str1 = (char*)malloc(20);
    char *str2 = (char*)malloc(20);
    strcpy(str1,"the");
    strcpy(str2,"that");
    const char *test = my_strcat(str1, str2);
    printf("%s\n", test);
    printf("%d\n", my_strcmp_rec(str1, str2));
    printf("%d\n", atoi("a823j6"));

    struct node **graph = (struct node**)malloc(sizeof(struct node*)*10);
    for (char i = 0; i < 10; ++i)
        graph[i]=(struct node*)malloc(sizeof(struct node));
    
    graph[0]->next = graph[1];
    graph[1]->next = graph[2];
    graph[2]->next = graph[3];
    graph[3]->next = graph[4];
    graph[4]->next = graph[5];
    printf("%d\n", floyd(graph[0]));

    for(char i = 0; i < 10; ++i)
        free(graph[i]);
    free(graph);
    return 0;
}
 
/*
float 
1 bit + 8 bits(z) (1(sign)+7(value)) + 23 bits(x) = 32 bits = 4 bytes
sign    exponent base

+/-    x2^z *x

2^23 * 2^2^7
0 = +/-  * 2^-127


double 
1 bit + 16 bits(z) (1(sign)+15(value)) + 52 bits(x) = 64 bits = 8 bytes

np.float64 struct float128{double x1; double x2;}

*/
