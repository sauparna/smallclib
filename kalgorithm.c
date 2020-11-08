#include "kalgorithm.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***************************************************************************/
/* Prototypes                                                              */
/***************************************************************************/

static long quick_sort_partition(long* a, long p, long r);

/***************************************************************************/
/* Functions                                                               */
/***************************************************************************/

unsigned long fibonacci(const unsigned long n)
{
    if (n == 0 || n == 1)
    {
        return n;
    }
    int c, a, b;
    a = 0;
    b = 1;
    for (int i = 2; i <= n; ++i)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

unsigned long fibonacci_naive_recursive(const unsigned long n)
{
    /* WARN: For pedagogic purposes only, never use this, the tree of recursive calls grow exponentially and therefore this is extremely inefficient.
     */
    if (n == 0 || n == 1)
    {
        return n;
    }
    else
    {
        return fibonacci_naive_recursive(n - 1) + fibonacci_naive_recursive(n - 2);
    }
}

void swap_int(long* const a, long* const b)
{
    long t = *a;
    *a = *b;
    *b =  t;
}

void swap_diff(long* const a, long* const b)
{
    if (a == b) return;
    *a -= *b; *b += *a; *a = *b - *a;
}

void swap_xor(long* const a, long* const b)
{
    if (a == b) return;
    *a ^= *b; *b ^= *a; *a ^= *b;
}

void quick_sort(long* a, long p, long r)
{
    if (p >= r)
    {
        return;
    }
    long q = quick_sort_partition(a, p, r);
    quick_sort(a, p, q - 1);
    quick_sort(a, q + 1, r);
}

static long quick_sort_partition(long* a, long p, long r)
{
    long x = a[r];
    long i = p - 1;
    for (long j = p; j <= r - 1; ++j)
    {
        if (a[j] < x)
        {
            i = i + 1;
            swap_int(&a[i], &a[j]);
        }
    }
    i = i + 1;
    swap_int(&a[i], &a[r]);
    return i;
}

/* PROBLEM: Find all possible ways of summing m integers to n.

   Given a positive integer n and a set of m positive integers less than or equal to n, find all combinations of the elements of the set that would sum to n. 
   
   For example, if n = 3 and the set A = {1, 2, 3} then three possible ways are:
   1 + 1 + 1
   1 + 2
   3
   
   ALGORITHM:
   
   The algorithm starts by splitting n into two, n and n - A[i], where i = 0, and recursively computing the splits for n - A[i]. At each call, n - A[i] are computed for p <= i <= m, where m = |A|. p is the value of i at which the function calls itself. This allows only the subsequent elements of the set to be used to create new splits and avoids computing 2 + 1 when 1 + 2 has already been found (as in the example above).
   
   The stopping condition for the recursive calls is n = 0, that is, when subtraction of A[i] from n repeatedly has reduced it to zero which indirectly means we have found the numbers that sum to n.

   NOTES:

   a) This is also the solution for the rod-cutting problem, where, given a rod of length n, you determine how many ways that can be split into pieces. The set A in this problem is set of integers in [1, n]: all the possible cut sizes.
*/

/* FINDOUT:
   a) Profile the code and see if the check below reduces function calls. When you remove this check, remember to uncomment the n < 0 check above.
   b) Is memory usage improved when we pass around v by reference and not by value?

*/

/* FIXIT:
   a) This is incomplete for want to a list-of-lists design and test using the kak library. We're coming back here after completing linked list API.
   b) A prototipical implementation is is ~/rough/rough.c, so refer to it when writing this up.
*/
