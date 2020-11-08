#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>

#include "./ktree.h"
#include "./ktests.h"
#include "./ktests_tree.h"

#define NNODES 9

static const long tree_data[NNODES] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

static node_t* create_binary_tree();
static void destroy_binary_tree(node_t* node_array, const size_t sz);
static void TEST_OBSERVERS();
static void TEST_TRAVERSAL_INORDER();


/* Initialize and link up the nodes to create the binary tree:

                          0
                        /   \
                       1     2
                      /    /   \
                     3    4     5
                           \   / \
                            6 7   8
*/
static node_t* create_binary_tree()
{
    node_t* node[NNODES];
    for (size_t i = 0; i < NNODES; ++i)
    {
        node[i] = node_new((void* const)&tree_data[i], 2);
    }

    node_add_link(node[0], LEFT,  node[1]);
    node_add_link(node[0], RIGHT, node[2]);
    node_add_link(node[1], LEFT,  node[3]);
    node_add_link(node[2], LEFT,  node[4]);
    node_add_link(node[2], RIGHT, node[5]);
    node_add_link(node[4], RIGHT, node[6]);
    node_add_link(node[5], LEFT,  node[7]);
    node_add_link(node[5], RIGHT, node[8]);

    return node[0];
}

/* INCOMPLETE: */
static void destroy_binary_tree(node_t* node_array, const size_t sz)
{
}

void run_binary_tree_tests()
{
    TEST_OBSERVERS();
    TEST_TRAVERSAL_INORDER();
}

static void TEST_OBSERVERS()
{
    char msg_observer[] = "Observers.";
    node_t* p = create_binary_tree();

    long a[3];
    a[0] = *((long* const)node_get_data(p));
    a[1] = *((long* const)node_get_data(node_get_link(p, LEFT)));
    a[2] = *((long* const)node_get_data(node_get_link(p, RIGHT)));

    long e[3] = {0, 1, 2};

    ktest_expect_equal((void*)a, (void*)e, sizeof(long) * 3, msg_observer);
    destroy_binary_tree(p, NNODES);
}

static void TEST_TRAVERSAL_INORDER()
{
    char msg_inorder[] = "Inorder traversal.";
    node_t* tree = create_binary_tree();
    
    void* traversed_element[NNODES];
    for (size_t i = 0; i < NNODES; ++i)
    {
        traversed_element[i] = NULL;
    }

    tree_traverse_inorder(tree, traversed_element);

    long traversed_a[NNODES];
    for (size_t i = 0; i < NNODES; ++i)
    {
        traversed_a[i] = *(long*)traversed_element[i];
    }
    
    long traversed_e[NNODES] = {3, 1, 0, 4, 6, 2, 7, 5, 8};
    
    ktest_expect_equal((void*)traversed_a, (void*)traversed_e, sizeof(long) * NNODES, msg_inorder);

    destroy_binary_tree(tree, NNODES);
}
