#include "autocomplete.h"





// includes



#include <assert.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stddef.h>

#include <ctype.h>

#include <time.h>

#include <math.h>



// repetition

#define rep(n) for(uint __i=0;__i<n;++__i)

#define repS(n) for(uchar __i=0;__i<n;++__i)

#define LOOP while(1)



// comparison

#define max(a,b) a>b?a:b

#define min(a,b) a<b?a:b



#define swap(a,b) void *tmp;tmp=a;a=b;b=tmp;



// scanning



#define scanint(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)

char _;

#define scanstr(s) scanf("%s",s);

#define scanfloat(s) scanf("%f",&s);

#define scandouble(s) scanf("%lf",&s);



// printing

#define printint(i) printf("%d\n",i);

#define printlong(i) printf("%lld\n",i)

#define printfloat(i) printf("%f\n",i);

#define printstr(i) printf("%s\n",i);

#define printarr(arr,len,format) for(size_t __ind=0;__ind<len;++__ind)printf(format,arr[__ind]);printf("\n");



// printing 2d arrays

#define print2arr(arr,h,w,format) for(size_t __h=0;__h<h;++__h)\
{for(size_t __w=0;__w<w;++__w)printf(format,arr[__h][__w]);printf("\n");}printf("\n");



#define print2arrColMajor(arr,w,h,format) for(size_t __h=0;__h<h;++__h)\
{for(size_t __w=0;__w<w;++__w)printf(format,arr[__w*h+__h]);printf("\n");}printf("\n");



#define print2arrRowMajor(arr,w,h,format) for(size_t __h=0;__h<h;++__h)\
{for(size_t __w=0;__w<w;++__w)printf(format,arr[__w+w*__h]);printf("\n");}printf("\n");



// search

// the arguments are : arr:array; size:size of array; val:value to find; ind:index (the answer is stored here);  

#define bSearch(arr,size,val,ind) {uint low=0,high=size-1,mid;ind=-1;\
while(low<=high){mid=(low+high)>>1;\
if(arr[mid]>val)high=mid-1;\
else if(arr[mid]<val)low=mid+1;\
else{ind=mid;break;}}}



#define bSearchL(arr,size,val,ind) {uint low=0,high=size-1,mid;ind=-1;\
while(low<=high){mid=(low+high)>>1;\
if(arr[mid]>val)high=mid-1;\
else if(arr[mid]<val)low=mid+1;\
else if(mid==0||arr[mid-1]!=val){ind=mid;break;}\
else {high=mid-1;}}}



#define bSearchR(arr,size,val,ind) {uint low=0,high=size-1,mid;ind=-1;\
while(low<=high){mid=(low+high)>>1;\
if(arr[mid]>val)high=mid-1;\
else if(arr[mid]<val)low=mid+1;\
else if(mid==size-1||arr[mid+1]!=val){ind=mid;break;}\
else {low=mid+1;}}}



#define lSearch(arr,size,val,ind) for(uint __ind=0;__ind<size;++__ind){if(arr[__ind]==val){ind=__ind;break;}}



// suprise! you can't name your variable gumboots anymore HA!

#define gumboots while(1) printf("Gumboots!\n");



// short-hand types

typedef long long ll;

typedef unsigned long long ull;

typedef unsigned int uint;

typedef unsigned char uchar;

typedef unsigned short ushort;

typedef long double ld;



typedef char* string;







typedef struct term Term;



#define _CRT_SECURE_NO_WARNINGS



static int cmpfunc(const void* a, const void* b)

{

    return strcmp(((Term*)a)->term, ((Term*)b)->term);

}



static int cmp(const char *str, const char *substr)

{

    size_t i = 0;

    while(str[i]&&substr[i])

    {

        if(str[i]==substr[i])

            ++i;

        else 

            return 0;

    }

    return 1;

}



/*

 * Part 1

 * ======

 * Write a function with the signature 

 *

 * void read_in_terms(struct term **terms, int *pnterms, char *filename);

 *

 * The function takes in a pointer to a pointer to struct term, a pointer to an int, 

 * and the name of a file that is formatted like cities.txt.

 * The function allocates memory for all the terms in the file and stores 

 * a pointer to the block in *terms. The function stores the number of terms in *pnterms.

 * The function reads in all the terms from filename, and places them in the block pointed to by *terms.

 */



void read_in_terms(Term **terms, int *pnterms, char *filename)

{

    char line[200], num[11];

    FILE *fp = fopen(filename, "r");

    fgets(num, sizeof(num), fp);

    *pnterms = atoi(num);





    *terms = (Term*)calloc(*pnterms,sizeof(Term));



    #ifdef DEBUG

        printint(sizeof((*terms)[1]));

    #endif

    for(uint __i=0;__i< *pnterms;++__i)

    {

        fscanf(fp, "%lf %200[^\n]", &((*terms)[__i].weight), &line);

        assert(line);

        strcpy((*terms)[__i].term, line);

        #ifdef DEBUG

        printstr((*terms)[__i]);

        #endif

    }

    fclose(fp);



    qsort(*terms, *pnterms, sizeof(Term), cmpfunc);

}



/*

 * Part 2(a)

 * =========

 * Write a function with the signature

 * int lowest_match(struct term *terms, int nterms, char *substr);

 *

 * The function returns the index in terms of the first term in lexicographic ordering that matches the string substr.

 *

 * This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.

 *

 * You can assume that terms is sorted in ascending lexicographic ordering.

 */



int lowest_match(Term *terms, int nterms, char *substr)

{

    int low = 0, mid, high = nterms - 1;

    char tmp[201]; // the temporary place to store the strings



    while (low<=high)

    {

        mid = (low+high)>>1;  // >>1 is the same as /2 but faster



        memcpy(tmp, terms[mid].term, sizeof(char) * strlen(substr)); // copy the first part of the string

        tmp[strlen(substr)] = 0;



        int diff = strcmp(tmp, substr); //does second term - first term strcmp(a,b) = -1



        #ifdef DEBUG

        printf("diff %d substr %s term %s\n", diff, substr, terms[mid].term);

        printf("low %u high %u mid %u\n", low, high, mid);

        #endif

        

        if (diff < 0)

            low = mid + 1;

        else if (diff > 0)

            high = mid - 1;

        else if (mid == 0)

            return mid;

        else

        {

            char prev[201];

            memcpy(prev, terms[mid - 1].term, sizeof(char)*strlen(substr));

            prev[strlen(substr)] = 0;

            if (strcmp(prev, tmp))

                return mid;

            high = mid - 1;

        }

    }

}



// a ab c



// Part 2(b)

// =========

// Write a function with the signature

// int highest_match(struct term *terms, int nterms, char *substr);



// The function returns the index in terms of the last term in lexicographic order that matches the string substr.



// This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.



// You can assume that terms is sorted in ascending lexicographic ordering.



int highest_match(Term *terms, int nterms, char *substr)

{

    int low = 0, mid, high = nterms - 1;

    char tmp[201]; // the temporary place to store the strings

    memset(tmp, 0, 201);



    while (low <= high)

    {

        mid = (low + high) >> 1;  // >>1 is the same as /2 but faster

        

        memcpy(tmp, terms[mid].term, sizeof(char) * strlen(substr)); // copy the first part of the string

        tmp[strlen(substr)] = 0;



        int diff = strcmp(tmp, substr); //does second term - first term strcmp(a,b) = -1



#ifdef DEBUG

        printf("diff %d substr %s term %s\n", diff, substr, terms[mid].term);

        printf("low %u high %u mid %u\n", low, high, mid);

#endif



        if (diff < 0)

            low = mid + 1;

        else if (diff > 0)

            high = mid - 1;

        else if (mid == nterms - 1)

            return mid;

        else

        {

            char prev[201];

            memset(prev, 0, 201);

            memcpy(prev, terms[mid + 1].term, sizeof(char) * (strlen(substr)));

            prev[strlen(substr)] = 0;

            if (strcmp(prev, tmp))

                return mid;

            low = mid + 1;

        }

    }

}



// Part 3s

// ======

// Write a function with the signature 



// void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr);



// The function takes terms (assume it is sorted lexicographically), the number of terms nterms, and the query string substr, and places the answers in answer, with *n_answer being the number of answers. The answer should be sorted by weight.



static int compar(const void* p1, const void* p2)

{

    return ((Term*)p2)->weight - ((Term*)p1)->weight;

}





void autocomplete(Term **answer, int *n_answer, Term *terms, int nterms, char *substr)

{

    int low, high;

    low = lowest_match(terms, nterms, substr); 

    high = highest_match(terms, nterms, substr);



    *n_answer = high - low + 1;

    

    *answer = (Term*)calloc(*n_answer, sizeof(Term));

    memcpy(*answer, terms+low, (*n_answer)*sizeof(Term));

    if (*answer && *n_answer>1)

        qsort(*answer, *n_answer, sizeof(Term), compar);

}
