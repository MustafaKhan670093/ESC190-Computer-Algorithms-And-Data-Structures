/* CSC190 notes:
 * PLEASE FOLLOW INSTRUCTIONS TO EXECUTE:
 * 1. COMPILE with G++ NOT GCC to include the bits/stdc++.h (basically includes everything) library because I'm lazy.
 *    command: g++ -o notes notes.cpp
 * 2. Execute the program with the following arguments:
 *      First: PASSWORD IS: I am sorry to hear about everyones laundry and praxis-related problems
 * 3. After the password is entered, list which lectures' notes you want to run. 
 * For example, if I want to run the notes from lectures 1 and 2 I would execute the command: ./notes [ENTER PASSWORD] 1 2
 */
#ifdef __cplusplus
#include<bits/stdc++.h>
#endif
int lec1();
int lec2();
int lec3();
int lec4();
int lec5();
int lec6();
/*,,,*/
int main(int argc, char* argv[])
{
    if (argc <= 12)
    {
        printf("insufficient arguments provided\n"); 
        exit(1);
    }

    if (strcmp(argv[1],"I")||strcmp(argv[2],"am")||strcmp(argv[3],"sorry")||strcmp(argv[4],"to")||strcmp(argv[5],"hear")||strcmp(argv[6],"about")||strcmp(argv[7],"everyones")||strcmp(argv[8],"laundry")||strcmp(argv[9],"and")||strcmp(argv[10],"praxis-related")||strcmp(argv[11],"problems"))
    {
        printf("password incorrect\n");
        exit(69);
    }
    
    for (int n=12;n<argc;++n)
    {
        switch(atoi(argv[n]))
        {
            case 1: printf("[exit code %d]\n",lec1()); break;
            case 2: printf("[exit code %d]\n",lec2()); break;
            case 3: printf("[exit code %d]\n",lec3()); break;
            case 4: printf("[exit code %d]\n",lec4()); break;
            case 5: printf("[exit code %d]\n",lec5()); break;
            case 6: printf("[exit code %d]\n",lec6()); break;
            /*...*/
            default: printf("invalid argument(%d) provided\n", atoi(argv[n])); exit(2);
        }
    }
    return 0;
}

/* lecture 1 */

void change_a (int *p_a)
{
    *p_a = 42;
}

int lec1()
{
    // single line comments
    
    /* multi
     * line
     * comments
     */
    int a = 0, b = 1, grade = 97;
    const char *mike = "mike", *jake = "jake";

    printf("2*a = %d\n", 2*a); 
    // %d: int
    // %s: string (const char*)
    // %c: character
    // %f: floating point
    // also useful %.2f: floating point to 2 decimal places
    
    printf("name = %s, name2 = %s, course= %d\n", mike, jake, 190);
    // printf with multiple % the argument

    //int statements
    if (grade>=50)
    {
        printf("pass\n");
    }
    else if (grade>=0)
        // single line statememts does not require {}. But putting them does not change the functionality of the program.
        printf("fail\n"); 

    // pointers
    int *p_b = &b; // &b means address of b. the pointer holds a memory address
    
    // Here you have dereferenced a pointer. Thus, you have become a cultured programmer.
    printf("the address of a is: %ld, the value is: %d\n", (long)p_b, *p_b);

    printf("a was %d ", a);
    change_a(&a);
    printf("a is now %d\n", a);

    return 0;
}

/* lecture 2 */

// swap the values at addresses given by p_a and p_b
void swap(int* p_a, int* p_b)
{
    int temp;
    temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;
}

int lec2()
{
    int a;
    // int* is a pointer type.
    int* p_a = &a;
    // int** is a pointer to pointer type.
    int** pp_a = &p_a;
    // %p prints the memory addresses in hexadecimal rather than decimal
    printf("%p %p\n", p_a, pp_a);

    int b = 4, c = 6;
    swap(&b, &c);
    printf("%d %d\n", b, c);

    return 0;
}

/* lecture 3 */
void f1(int a[]) {*a=5; a[1]=6;} // when an array is passed to a function, it passes a pointer to first element of the array.
void f2(int* a) {a[0]=5; *(a+1)=6;} // f1 and f2 are equivilent. *a and a[0] are equivilent.

int lec3()
{
    // Constant Size C arrays:
    const int size = 3;
    int arr[size]; // you can declare an array. this allocates a contiguous block of memory with size size*sizeof(int) on the stack.
    
    // the uninitialized array elements are going to be whatever the memory values initially.
    printf("This is basically a random number: %d\n", arr[1]);

    int a[3] = {2,3,4}; // you can declare and initialize an array.
    
    f1(arr); f2(a);
    printf("a[0]'s value after: f1 is %d, f2 is %d.\n", arr[0], a[0]);

    int *p_a = &a[0]; // p_a can be used like a is.
    
    printf("a = {%d %d %d}\n", *p_a, *(p_a+1), *(p_a+2)); // a[1] is the same as *(a+1). 
    // They both access the address of the pointer a + 1*sizeof(int)

    // size_t sizeof(type) function returns the size (in bytes) of the given type
    printf("\nsize of int: %d\nsize of float: %d\nsize of long double: %d\nsize of void pointer: %d\nsize of char: %d\nsize of a: %d\nsize of p_a: %d\n", (int)sizeof(int), (int)sizeof(float), (int)sizeof(long double), (int)sizeof(void*), (int)sizeof(char), (int)sizeof(a), (int)sizeof(p_a));
    
    return 0;
}

/* lecture 4 */
void print_arr(int *arr, size_t size)
{
    size_t i = 0;
    printf("[");
    for (i = 0; i < size; ++i)
        printf("%d ", arr[i]);
    printf("]\n");
}

// more complex data types: the struct

typedef struct  
    {
        int esc180_mark;
        int phy180_mark;
    } student_record;
int lec4()
{
    /* binary and hexadecimal:
     * on a computer, everything is stored in binary.
     * i.e. 1011 = 1* 2^3 + 0* 2^2 + 1* 2^1 + 1* 2^0 = 8+0+2+1=11
     * 8 bits (ie binary digits) is 1 byte. It is commonly represented as 2 digits in hexadecimal.
     */

    student_record student1;
    student1.esc180_mark = 85;
    student1.phy180_mark = 85;
    // student_record student1 = {85, 85}; does the same thing

    printf("%d\n", (int)sizeof(student_record));

    student_record *h_student1 = &student1;
    h_student1->esc180_mark; // these two lines are equivilent
    (*h_student1).esc180_mark;
    
    // h_student1.esc180_mark; don't do this please it is an error
    return 0;
}

/* lecture 5 */

void f(student_record s)
{
    s.esc180_mark = 100;
    // this function will not have an effect
    // since s is copied.
}

void f1(int *a)
{
    *a = 100;
}

void f2(student_record *ps)
{
    (*ps).esc180_mark = 100; // has an effect
    ps->esc180_mark = 100; // does the same thing as the line above.
}

int* make_arr(size_t size)
{
    return (int*)malloc(size);
}

int* make_arr10_wrong()
{
    int a[10];
    return a;
}

int lec5()
{
    student_record s, s1;

    // you can define a variable
    s.esc180_mark = 94;
    s1.phy180_mark = 95;
    printf("%p %p %p\n", &s, &s.esc180_mark, &s.phy180_mark);
    // student1 points to the address of the first field.

    f(s); // does nothing
    f1(&s.esc180_mark); // has an effect, but it's just treating the struct as an integer
    f2(&s);

    // malloc allocates memory on the heap and returns a void* to the memory.
    int *a = (int*)malloc(10*sizeof(int));

    // free your memory please
    free(a);
    return 0;
}

/* lecture 6 */

// linked list
// first implement the nodes of the list 
struct node
{
    int data; //this is your data
    struct node *next; // this is the pointer to the next element
    // Point the last element to the NULL pointer to signify the last element
};

void append(struct node *head, int value)
{
    while (head->next!= NULL)
        head = head->next;
    struct node *tail = (struct node*)malloc(sizeof(struct node));
    head->next = tail;
    tail->data = value;
    tail->next = NULL; 
}

int max(struct node *head)
{
    int max = head->data;
    while(head!=NULL)
    {
        if (head->data>max)
            max = head->data;
        head = head->next;
    }
    return max;
}

int lec6()
{
    // create the first node
    struct node *node0 = (struct node*)malloc(sizeof(struct node));
    node0->data=3;

    // create the second node
    struct node *node1 = (struct node*)malloc(sizeof(struct node));
    node0->next=node1; // link node0 to node1
    node1->data=5; // add the data
    node1->next=NULL; // terminate the linked list

    // free your memory, please.
    free(node0);
    free(node1);
    return 0;
}

int my_strlen(const char *s1)
{
    int len = 0;
    while (*s1!='\0')
    {
        len++;s1++;
    }
    return len;
}
void my_strcpy (char *dest, char *src)
{
    while(*src!='\0') *dest++=*src++;
}
/* lecture 8 */
int lec8()
{
    // characters are single symbols within ''. They are also numbers (0-255)
    char c1 = 'a';
    char c2 = 'A';

    // string literals are in double quotes.
    const char* s1 = "asdflkjasdflkj";
    // When declared like this, the string will be placed in a special area of memory with the number of characters + 1
    // Strings end with a null terminator.

    // To stores strings on the stack of the heap respectively,
    char s2[15] = "asdflkjasdflkj";
    
    char *s3 = (char*)malloc(4*sizeof(char));
    s3 = "abc";
    // "abc" stores {'a', 'b', 'c', '\0'}

    // there is a string library in the file string.h (included in bits/stdc++.h already)

    // to copy strings
    
    strcpy(s2,s1);
}

/* lecture 9 */

struct Stack{
    int *data;
    int size;
    int n;
};
void create_stack(struct Stack *stack)
{
    stack->size = 1;
    stack->data = (int*)malloc(stack->size*sizeof(int));
    stack->n = 0;
}
void push(struct Stack *stack, int elem)
{
    if (stack->size>=stack->n)
    {
        stack->size<<=1;
        stack->data = (int*)realloc(stack->data,stack->size*sizeof(int));
        assert(stack->data);
    }
    stack->data[stack->n++] = elem;
}
int pop(struct Stack *stack)
{
    return stack->data[--stack->n];
}

/* etc... */
