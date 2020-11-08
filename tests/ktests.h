#ifndef _KTESTS_H_
#define _KTESTS_H_

#include <sys/types.h>
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/***************************************************************************/
/* Globals                                                                */
/***************************************************************************/

// Precomputed array of fibonacci numbers
static const long fibs[55] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903, 2971215073, 4807526976, 7778742049, 12586269025, 20365011074, 32951280099, 53316291173, 86267571272};

static bool test_verbose = false;

/***************************************************************************/
/* Prototypes                                                              */
/***************************************************************************/

int cmp_long(const void* const a_, const void* const b_);

void ktest_str_expect_equal_internal(const char* const a, const char* const e, const size_t sz, const char* const func_name, const int line, char* msg);

void ktest_array_expect_equal_internal(const long* const a, const long* const e, const size_t sz, const char* const func_name, const int line, char* msg);

void ktest_expect_equal_internal(const void* const a, const void* const e, const size_t bytes, const char* const func_name, const int line, char* msg);

void run_stack_tests();
void run_binarytree_tests();
void run_sort_tests();
void run_list_tests();

/***************************************************************************/
/* Macros                                                                  */
/***************************************************************************/

/* Marks a test as successful, outputting its name and line. */
#define TEST_PASS(msg) \
    TEST_PASS_WITH_NAME(__func__, __LINE__, msg)

/* Marks a test as successful, outputting the specified name and line. */
#define TEST_PASS_WITH_NAME(name, line, msg)                            \
    do {                                                                \
        fprintf(stderr, ANSI_COLOR_YELLOW "%30s" ANSI_COLOR_RESET " : %-5d : " ANSI_COLOR_CYAN "PASS" ANSI_COLOR_RESET  " : %-100s\n", (name), (line), (msg)); \
    } while (0)
          
/* Marks a test as unsuccessful, outputting its name, line and the specified failure message.

   Use this macro just like you would call printf.
*/
#define TEST_FAIL(failure_msg, args...) \
    TEST_FAIL_WITH_NAME(__func__, __LINE__, failure_msg, ##args)

/* Marks a test as unsuccessful, outputting the specified name, line and failure message. 

   Use this macro just like you would call printf.
*/
#define TEST_FAIL_WITH_NAME(name, line, failure_msg, args...)           \
      do {                                                              \
          fprintf(stderr, ANSI_COLOR_MAGENTA "%30s" ANSI_COLOR_RESET " : %-5d : " ANSI_COLOR_MAGENTA "FAIL" ANSI_COLOR_RESET " : ", \
                  (name), (line));                                      \
          fprintf(stderr, (failure_msg), ##args);                       \
          fprintf(stderr, "\n");                                        \
      } while (0)
      
/* Calls ktest_stack_expect_internal with the current function and line number.
 */
#define ktest_stack_expect(x, sz)                              \
    ktest_stack_expect_internal((x), (sz), __func__, __LINE__)

#define ktest_str_expect_equal(a, e) \
    ktest_str_expect_equal_internal((a), (e), __func__, __LINE__)

#define ktest_array_expect_equal(a, e, sz) \
    ktest_array_expect_equal_internal((a), (e), (sz), __func__, __LINE__)

#define ktest_expect_equal(a, e, bytes, msg, args...)                           \
          ktest_expect_equal_internal((a), (e), (bytes), __func__, __LINE__, msg, ##args)


#endif // _KTESTS_H_
