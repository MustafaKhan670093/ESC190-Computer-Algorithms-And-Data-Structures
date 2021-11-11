/*
ESC190 2020 Final Exam: http://exams.skule.ca/exams/CSC190H1_20201_631587814485Final%20Assessment%20Crowdmark.pdf

Q1. 

a. 

h2(x) is better (and therefore reccomended) than h1(x) because it does not cause the hashed outputs to cluster as easily.

An example of h1(x) producing clustered values is for h1(5) = h1(6) = h1(7), whereas h2(5), h2(6) 
and h2(7) all produce unique answers.

Thus in h1(x), the floor function paired with the squareroot makes it more likely for the same values 
to appear out of the hash function, which means there is a higher chance of collissions occuring.

b. 

Indicate which of the following hash table modes you would recommend to Alice:
i. Closed addressing with chaining using linked lists
ii. Closed addressing with chaining using binary search trees
iii. Open addressing with linear probing
iv. Open addressing with quadratic probing

Justify your choice. Describe 2-3 relevant implementation considerations.

I would reccomend using iv., open addressing with quadratic probing. 

Compared to closed addressing, open addressing has:
- Better memory locality and cache performance as 
  all elements laid out linearly in memory.
- Performs better than closed addressing when the number 
  of keys is known in advance and the churn is low.
- No size overhead apart from the hash table array.

Additionally, although closed addressing has no issues with 
clustering and has no theoretical maximum load factor, 
its derformance degrades as load factor grows. This could 
be the better choice for low load factors.

Compared to linear probing, quadratic probing:
- Avoids clustering much better as it probes more widely

Note however, that linear probing is a simpler computation. These
are the aspects of each selection that needs to be considered.

More arguments here: https://www.geeksforgeeks.org/hashing-set-3-open-addressing/


Question #1.2
Suppose the balance factors of nodes n and z are 𝑏𝑛𝑟𝑖𝑔ℎ𝑡
and 𝑏𝑧𝑟𝑖𝑔ℎ𝑡, respectively, in the right BST and 𝑏𝑛𝑙𝑒𝑓𝑡 and 𝑏𝑧𝑙𝑒𝑓𝑡 , 
respectively, in the left BST. Derive closed-form
expressions for 𝑏𝑛𝑙𝑒𝑓𝑡 and 𝑏𝑧𝑙𝑒𝑓𝑡 in terms of 𝑏𝑛𝑟𝑖𝑔ℎ𝑡 and 𝑏𝑧𝑟𝑖𝑔ℎ𝑡
after a left rotation is applied to the right BST.

b_nleft = bn_right + 1
b_zleft = b_zright + 2

Question #1.3


/*
Your calculator is broken, and you need to calculate the 
logarithm of a number 𝑥 with a specific base. Implement 
an efficient algorithm in C that runs in 𝑂(log 𝑥) time to find the
𝑛th base logarithm of a number 𝑥 ≥ 1 up to a certain tolerance 𝜀. 
You may use only the following functions from math.h:
 - double pow(double base, double exp)
 - double fabs(double num)
 */

#include <math.h>

/*
 x: number to take the logarithm of
 n: number specifying which logarithm base to apply
 epsilon: tolerance
 */

double find_nth_log(double x, double n, double epsilon){
    
    while answer < epsilon
    
    sum = 0
    while sum <
}