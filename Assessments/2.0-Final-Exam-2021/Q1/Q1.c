#include "Q1.h"

#include <stdio.h>
#include <stdlib.h>
#define MAX_CHARS 256

// Note: I set the max number of characters to be the total number of ascii characters that are there.

/*******************
* Helper Function. *
********************/

/*
The following function traverses s2 and returns a 256 spaces long array
containing the count of each character in s2. Different indices of the array
correspond to different ascii characters.
*/

int* numCharsArray(char* s2)
{
    int* count = (int*)calloc(sizeof(int), MAX_CHARS);
    int i;
    for (i = 0; *(s2 + i); i++)
        count[*(s2 + i)]++;

        for(int i = 0; i < 256; i++) {
        // printf("%d ", count[i]);
        // printf("\n");
    }
    return count;
}

/*
The following is the function we were tasked with writing. 
I traverse through each character in s1 and see if 
it exists in the numCharsArray of s2. If it is NOT (i.e if count[temp] == 0),
then I add that value to the resulting string. Else, I skip it.
In the end, I add a null terminator to the resulting string.
*/

void remove_str(char *s1, char *s2){
    int* count = numCharsArray(s2);
    int traverse_index = 0, resulting_index = 0;
    while (*(s1 + traverse_index))
    {
        char temp = *(s1 + traverse_index);
        if (count[temp] == 0)
        {
            *(s1 + resulting_index) = *(s1 + traverse_index);
            resulting_index++;
        }
        traverse_index++;
    }
    *(s1 + resulting_index) = '\0';
}