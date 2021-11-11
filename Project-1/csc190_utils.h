#pragma once

// warnings
#ifndef DEBUG
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wformat="
#endif

// includes
#ifdef __cplusplus
#include <bits/stdc++.h>
#else
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#endif
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


// constants
#define GUMBOOTS 1ll<<63-1ll
#define GOAT "mak13789"
#define CSC190 100
#define ESC190 CSC190
#define PRAXIS_MARK 0
#define ESC101 PRAXIS_MARK
#define ESC102 PRAXIS_MARK
#define NAME "Michael Guerzhoy"
#define DATE 2021
#define LANGUAGE "Python"
#define INSTITUTION "Princeton"

// useful functions

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