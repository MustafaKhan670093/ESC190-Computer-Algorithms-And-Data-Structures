#include "autocomplete.h"
#include "csc190_utils.h"

typedef struct term Term;

int cmpfunc(const void *a, const void *b)
{
    return strcmp(((Term*)a)->term, ((Term*)b)->term);
}

int main(int argc, char *argv[])
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    printint(lowest_match(terms, nterms, "Tor"));
    printint(highest_match(terms, nterms, "Tor"));
    printstr(terms[82641].term);
    highest_match(terms, nterms, "Tor");
    printstr(terms[82819].term);
    printstr(terms[82820].term);
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");
    //free allocated blocks here -- not required for the project, but good practice

    rep(n_answer)
    {
        printf("%lf %s\n", (answer+__i)->weight, (answer+__i)->term);
    }

    free(answer);
    free(terms);

    return 0;
}


//"barry", "battery", "barney", "bb"
//"ba*"

