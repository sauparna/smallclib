#ifndef KSTACK_H
#define KSTACK_H

#include <sys/types.h>
#include <stdbool.h>

/* Design notes:
   a) Variable names, for example, x for the stack, m for capacity and so on are in step with Knuth's exposition on stacks in TAOCP 2.2.1. It would have been ideal to be able to use upper case letter like X and M but that goes against the grain of writing C programs.
   b) The size and capacity of the stack are two distinct things. The size the number of elements in the stack and capacity (the member m in the the struct) is the total memory allocated to a stack. The invariant is 0 <= size <= m. They both have the same units of course; void* pointers.

 */

/***************************************************************************/
/* Types                                                                   */
/***************************************************************************/

typedef enum STACK_STATE {STACK_UNDERFLOW, STACK_OVERFLOW, STACK_OPERATION_SUCCEEDED} STACK_STATE_E;

typedef struct stack
{
    void** buf;
    size_t m;
    ssize_t t;
} stack_t;

/***************************************************************************/
/* Prototypes                                                              */
/***************************************************************************/

stack_t* stack_new(const size_t m);
void stack_free(stack_t* const x);

STACK_STATE_E stack_push(stack_t* const stack, void* data);
STACK_STATE_E stack_pop(stack_t* const stack, const void** popped_data);

ssize_t stack_get_top(const stack_t* const stack);
size_t stack_get_size(const stack_t* const stack);
size_t stack_get_capacity(const stack_t* const stack);
void** const stack_get_buf(const stack_t* const stack);

bool stack_empty(const stack_t* const stack);
bool stack_full(const stack_t* const stack);

#endif /* KSTACK_H */
