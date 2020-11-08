#ifndef KTREE_H
#define KTREE_H

#include <sys/types.h>

/***************************************************************************/
/* Types                                                                   */
/***************************************************************************/

typedef enum LINK_TYPE {LEFT = 0, RIGHT = 1} LINK_TYPE_E;

typedef struct node
{
    void* data;
    struct node** link;
} node_t;


/***************************************************************************/
/* Prototypes                                                              */
/***************************************************************************/

node_t* node_new(void* const data, const size_t nlink);
void node_free(node_t* const node);

void node_add_link(node_t* const node, LINK_TYPE_E ltype, node_t* const newnode);
node_t* const node_get_link(const node_t* const node, LINK_TYPE_E ltype);
void* const node_get_data(const node_t* const node);

void tree_traverse_inorder(node_t* tree, void** const traversed_element);

#endif // KTREE_H
