#ifndef KLIST_H
#define KLIST_H

#include <stdbool.h>
#include <sys/types.h>

/***************************************************************************/
/* Types                                                                   */
/***************************************************************************/

typedef struct lnode
{
    void* data;
    struct lnode* next;
} lnode_t;

typedef struct dlnode
{
    void* data;
    struct dlnode* next;
    struct dlnode* prev;
} dlnode_t;

/***************************************************************************/
/* Prototypes                                                              */
/***************************************************************************/

lnode_t* lnode_new(void* const data);
void lnode_free(lnode_t* ln);
lnode_t* list_add_front(lnode_t* list, lnode_t* const ln);
lnode_t* list_add_end(lnode_t* list, lnode_t* ln);

bool list_lookup(lnode_t* list, void* const data, int (*cmp)(const void* const a, const void* const b), const lnode_t** node, size_t* const index);

bool list_delete(lnode_t* list, void* const data, int (*cmp)(const void* const a, const void* const b), const lnode_t** node, size_t* const index);

void* lnode_get_data(const lnode_t* const node);
void lnode_set_data(lnode_t* const node, void* data);

#endif /* KLIST_H */
