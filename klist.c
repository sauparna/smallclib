#include <stdlib.h>
#include "./klist.h"

/***************************************************************************/
/* Functions                                                               */
/***************************************************************************/

lnode_t* lnode_new(void* const data)
{
    lnode_t* ln = malloc(sizeof(lnode_t));
    if (ln == NULL)
    {
        return NULL;
    }
    ln->next = NULL;
    ln->data = data;
    return ln;
}

void lnode_free(lnode_t* ln)
{
    if (ln == NULL)
    {
        return;
    }
    free(ln);
}

lnode_t* list_add_front(lnode_t* list, lnode_t* const ln)
{
    if (ln == NULL)
    {
        return list;
    }
    ln->next = list;
    return ln;
}

lnode_t* list_add_end(lnode_t* list, lnode_t* ln)
{
    if (ln == NULL)
    {
        return list;
    }
    if (list == NULL)
    {
        return ln;
    }
    lnode_t* p = list;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = ln;
    return list;
}

bool list_lookup(lnode_t* list, void* const data, int (*cmp)(const void* const a, const void* const b), const lnode_t** node, size_t* const index)
{
    int i = 0;
    *node = NULL;
    for (lnode_t* p = list; p != NULL; p = p->next, ++i)
    {
        if ((*cmp)(p->data, data) == 0)
        {
            *node = p;
            *index = i;
            return true;
        }
    }
    return false;
}

bool list_delete(lnode_t* list, void* const data, int (*cmp)(const void* const a, const void* const b), const lnode_t** node, size_t* const index)
{
    lnode_t* p = NULL;
    lnode_t* q = list;
    size_t i = 0;
    while (q != NULL)
    {
        lnode_t* r = q->next;
        if ((*cmp)(q->data, data) == 0)
        {
            *node = q;
            *index = i;
            if (p)
                p->next = q->next;
            else
                p = q->next;
            return true;
        }
        p = q;
        q = r;
        ++i;
    }
    return false;
}

void* lnode_get_data(const lnode_t* const node)
{
    if (node == NULL) return NULL;
    return node->data;
}

void lnode_set_data(lnode_t* const node, void* data)
{
    if (node == NULL) return;
    node->data = data;
}
