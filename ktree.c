#include "./ktree.h"
#include "./kstack.h"

#include <stdlib.h>

/***************************************************************************/
/* Functions                                                               */
/***************************************************************************/

node_t* node_new(void* const data, const size_t nlink)
{
    node_t** link = malloc(nlink * sizeof(node_t*));
    if (link == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < nlink; ++i)
    {
        link[i] = NULL;
    }
    node_t* node = malloc(sizeof(node_t));
    if (node == NULL)
    {
        free(link);
        return NULL;
    }
    node->data = data;
    node->link = link;
    return node;
}

void node_free(node_t* const node)
{
    if (node == NULL)
    {
        return;
    }
    free(node->link);
    node->link = NULL;
    free(node);
}

void node_add_link(node_t* const node, LINK_TYPE_E ltype, node_t* const newnode)
{
    node->link[ltype] = newnode;
}

node_t* const node_get_link(const node_t* const node, LINK_TYPE_E ltype)
{
    return node->link[ltype];
}

void* const node_get_data(const node_t* const node)
{
    return node->data;
}

void tree_traverse_inorder(node_t* tree, void** const traversed_element)
{
    stack_t* stack = stack_new(100);
    node_t* p = tree;
    int i = 0;
    while (1)
    {
        while (p != NULL)
        {
            stack_push(stack, (void*)p);
            p = node_get_link(p, LEFT);
        }
        if (stack_empty(stack) == true)
        {
            break;
        }
        const void* popped_node = NULL;
        stack_pop(stack, &popped_node);
        p = (node_t*)popped_node;
        traversed_element[i++] = p->data;
        p = node_get_link(p, RIGHT);
    }
}
