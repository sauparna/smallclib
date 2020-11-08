#include <stdlib.h>

#include "./ktests.h"
#include "./kstack.h"
#include "./ktests_stack.h"

#define NFIBS 5
#define STACK_SIZE 100

static stack_t* create_stack();
static void destroy_stack(stack_t* stack);
static void TEST_PUSH();
static void TEST_POP();

void run_stack_tests()
{
    TEST_PUSH();
    TEST_POP();
}

static stack_t* create_stack()
{
    return stack_new(STACK_SIZE);
}

static void destroy_stack(stack_t* stack)
{
    stack_free(stack);
}

static void TEST_PUSH()
{
    char msg_push[] = "Push.";
    char msg_size[] = "Size.";
    stack_t* stack = create_stack();
    long a[NFIBS], e[NFIBS];

    for (size_t i = 0; i < NFIBS; ++i)
    {
        stack_push(stack, (void*)&fibs[i]);
        e[i] = fibs[i];
    }

    void** stack_buf = stack_get_buf(stack);

    size_t stack_sz = stack_get_size(stack);
    size_t e_sz = NFIBS;
    ktest_expect_equal((void*)&stack_sz, (void*)&e_sz, sizeof(long), msg_size);

    for (size_t i = 0; i < stack_sz; ++i)
    {
        a[i] = *(long*)stack_buf[i];
    }
    ktest_expect_equal((void*)a, (void*)e, (sizeof(long) * NFIBS), msg_push);

    destroy_stack(stack);
}

static void TEST_POP()
{
    char msg_pop[]  = "Pop.";
    char msg_size[] = "Size.";
    stack_t* stack = create_stack();

    long a[NFIBS];
    for (size_t i = 0; i < NFIBS; ++i)
    {
        stack_push(stack, (void*)&fibs[i]);
    }

    long e[NFIBS - 1];
    for (size_t i = 0; i < NFIBS - 1; ++i)
    {
        e[i] = fibs[i];
    }
    
    const void* popped_element = NULL;
    stack_pop(stack, &popped_element);

    void** stack_buf = stack_get_buf(stack);
    size_t stack_sz = stack_get_size(stack);

    size_t e_sz = NFIBS - 1;
    ktest_expect_equal((void*)&stack_sz, (void*)&e_sz, sizeof(long), msg_size);

    for (size_t i = 0; i < stack_sz; ++i)
    {
        a[i] = *(long*)stack_buf[i];
    }
    
    ktest_expect_equal((void*)a, (void*)e, (sizeof(long) * (NFIBS - 1)), msg_pop);

    destroy_stack(stack);
}
