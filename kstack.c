#include <stdlib.h>
#include <sys/types.h>

#include "./kstack.h"

/***************************************************************************/
/* Functions                                                               */
/***************************************************************************/

stack_t* stack_new(const size_t m)
{
    void** const buf = malloc(m * sizeof(void*));
    if (buf == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < m; ++i)
    {
        buf[i] = NULL;
    }
    stack_t* const x = malloc(sizeof(stack_t*));
    if (x == NULL)
    {
        free(buf);
        return NULL;
    }
    x->buf = buf;
    x->m   = m;
    x->t   = -1;
    return x;
}

/* Assumption:
   a) Data elements pointed to by buf is not our responsibility. We assume they are in memory taken care of by the client. Here we simply deallocate the array of pointers that buf is, not the data each element of buf points to.
*/
void stack_free(stack_t* const x)
{
    if (x == NULL)
    {
        return;
    }
    free(x->buf);
    x->buf = NULL;
    free(x);
}

STACK_STATE_E stack_push(stack_t* const x, void* data)
{
    x->t = x->t + 1;
    if (x->t == x->m)
        return STACK_OVERFLOW;
    x->buf[x->t] = data;
    return STACK_OPERATION_SUCCEEDED;
}

STACK_STATE_E stack_pop(stack_t* const x, const void** popped_data)
{
    if (x->t == -1)
        return STACK_UNDERFLOW;
    *popped_data = x->buf[x->t];
    x->t = x->t - 1;
    return STACK_OPERATION_SUCCEEDED;
}

bool stack_empty(const stack_t* const x)
{
    if (x->t == -1)
        return true;
    return false;
}

bool stack_full(const stack_t* const x)
{
    if (x->t == x->m)
        return true;
    return false;
}

ssize_t stack_get_top(const stack_t* const stack)
{
    return stack->t;
}

size_t stack_get_size(const stack_t* const stack)
{
    return (ssize_t)stack->t + 1;
}

size_t stack_get_capacity(const stack_t* const stack)
{
    return stack->m;
}

void** const stack_get_buf(const stack_t* const stack)
{
    return stack->buf;
}
