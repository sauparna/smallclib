#ifndef KALGORITHM_H
#define KALGORITHM_H

#include <sys/types.h>

/***************************************************************************/
/* Macros                                                                  */
/***************************************************************************/

/***************************************************************************/
/* Prototypes                                                              */
/***************************************************************************/

unsigned long fibonacci(const unsigned long n);
unsigned long fibonacci_naive_recursive(const unsigned long n);
void swap_int(long* const a, long* const b);
void swap_diff(long* const a, long* const b);
void swap_xor(long* const a, long* const b);
void quick_sort(long* a, long p, long r);

#endif /* KALGORITHM_H */
