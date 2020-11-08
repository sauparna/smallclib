#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kalgorithm.h"
#include "kstack.h"
#include "ktree.h"
#include "klist.h"

#include "ktests.h"
#include "ktests_stack.h"
#include "ktests_list.h"
#include "ktests_tree.h"
#include "ktests_misc.h"
#include "ktests_sort.h"

/***************************************************************************/
/* Prototypes                                                              */
/***************************************************************************/

int ktest_intcmp(const void* a, const void* b);

/***************************************************************************/
/* Functions                                                               */
/***************************************************************************/

/* TODO: Rewrite it to have bad carry more information about the mismatch. */
void ktest_str_expect_equal_internal(const char* const a, const char* const e, const size_t sz, const char* const func_name, const int line, char* msg)
{
    const char* bad = NULL;
    for (size_t i = 0; i < sz; ++i)
    {
        if (a[i] != e[i])
        {
            bad = "string content";
            break;
        }
    }
    if (bad != NULL)
    {
        fprintf(stdout, "actual string:\n    ");
        for (size_t i = 0; i < sz; ++i)
        {
            printf("%c ", a[i]);
        }
        printf("\n");
        fprintf(stdout, "expected string:\n    ");
        for (size_t i = 0; i < sz; ++i)
        {
            printf("%c ", e[i]);
        }
        printf("\n");
        TEST_FAIL_WITH_NAME(func_name, line, "Incorrect %s.", bad);
    }
    else
    {
        TEST_PASS_WITH_NAME(func_name, line, msg);
    }
}

void ktest_array_expect_equal_internal(const long* const a, const long* const e, const size_t sz, const char* const func_name, const int line, char* msg)
{
    char *bad = NULL;
    for (size_t i = 0; i < sz; ++i)
    {
        if (a[i] != e[i])
        {
            bad = "array content";
            break;
        }
    }
    if (bad != NULL)
    {
        fprintf(stdout, "actual array:\n    ");
        for (size_t i = 0; i < sz; ++i)
        {
            printf("%ld ", a[i]);
        }
        printf("\n");
        fprintf(stdout, "expected array:\n    ");
        for (size_t i = 0; i < sz; ++i)
        {
            printf("%ld ", e[i]);
        }
        printf("\n");
        TEST_FAIL_WITH_NAME(func_name, line, "Incorrect %s.", bad);
    }
    else
    {
        TEST_PASS_WITH_NAME(func_name, line, msg);
    }
}

void ktest_expect_equal_internal(const void* const a, const void* const e, const size_t bytes, const char* const func_name, const int line, char* msg)
{
    char* bad = NULL;
    for (size_t i = 0; i < bytes; ++i)
    {
        if (*(char*)(a + i) != *(char*)(e + i))
        {
            bad = "content";
            break;
        }
    }
    if (bad != NULL)
    {
        TEST_FAIL_WITH_NAME(func_name, line, "Incorrect %s.", bad);
    }
    else
    {
        TEST_PASS_WITH_NAME(func_name, line, msg);
    }
}

int cmp_long(const void* const a_, const void* const b_)
{
    const long a = *(const long* const)a_;
    const long b = *(const long* const)b_;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

int main()
{
    run_swap_tests();
    run_list_tests();
    run_stack_tests();
    run_binary_tree_tests();
    run_sort_tests();

    return 0;
}
