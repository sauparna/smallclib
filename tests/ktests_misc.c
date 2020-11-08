#include "./ktests.h"
#include "./kalgorithm.h"
#include "./ktests_misc.h"

static void TEST_SWAP_INT();
static void TEST_SWAP_DIFF();
static void TEST_SWAP_XOR();

void run_swap_tests()
{
    TEST_SWAP_INT();
    TEST_SWAP_DIFF();
    TEST_SWAP_XOR();
}

static void TEST_SWAP_INT()
{
    char msg1[] = "One of the swapped variables.";
    char msg2[] = "The other swapped variable.";
    char msg3[] = "Overlap memory locations.";
    long x, y, ex, ey;

    x  = 1; y  = 2;
    ex = 2, ey = 1;
    swap_int(&x, &y);
    ktest_expect_equal((void*)&x, (void*)&ex, sizeof(long), msg1);
    ktest_expect_equal((void*)&y, (void*)&ey, sizeof(long), msg2);

    x = 1;
    ex = 1;
    swap_int(&x, &x);
    ktest_expect_equal((void*)&x, (void*)&ex, sizeof(long), msg3);
}

static void TEST_SWAP_DIFF()
{
    char msg1[] = "One of the swapped variables.";
    char msg2[] = "The other swapped variable.";
    char msg3[] = "Overlap memory locations.";

    long x, y, ex, ey;
    x  = 1; y  = 2;
    ex = 2, ey = 1;
    swap_diff(&x, &y);

    ktest_expect_equal((void*)&x, (void*)&ex, sizeof(long), msg1);
    ktest_expect_equal((void*)&y, (void*)&ey, sizeof(long), msg2);

    x = 1;
    ex = 1;
    swap_diff(&x, &x);
    ktest_expect_equal((void*)&x, (void*)&ex, sizeof(long), msg3);
}

static void TEST_SWAP_XOR()
{
    char msg1[] = "One of the swapped variables.";
    char msg2[] = "The other swapped variable.";
    char msg3[] = "Overlap memory locations.";

    long x, y, ex, ey;
    x  = 1; y  = 2;
    ex = 2, ey = 1;
    swap_xor(&x, &y);
    
    ktest_expect_equal((void*)&x, (void*)&ex, sizeof(long), msg1);
    ktest_expect_equal((void*)&y, (void*)&ey, sizeof(long), msg2);

    x = 1;
    ex = 1;
    swap_xor(&x, &x);
    ktest_expect_equal((void*)&x, (void*)&ex, sizeof(long), msg3);
}
