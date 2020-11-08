#include <stdlib.h>
#include "./ktests.h"
#include "./kalgorithm.h"

#define NELEMS 5

static void TEST_QUICK_SORT();

void run_sort_tests()
{
    TEST_QUICK_SORT();
}

static void TEST_QUICK_SORT()
{
    char msg_qsort[] = "Quicksort; CLRS.";

    long a[NELEMS] = {10, -1, 1, 2, -5};
    quick_sort(a, 0, NELEMS - 1);
    long e[NELEMS] = {-5, -1, 1, 2, 10};

    ktest_expect_equal((void*)a, (void*)e, sizeof(long) * NELEMS, msg_qsort);
}
  
