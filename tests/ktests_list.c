#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>

#include "./klist.h"
#include "./ktests.h"
#include "./ktests_list.h"

#define NFIBS 8

static lnode_t* create_list(size_t n)
{
    /*    indices -->  0 1 2 3  4 5 6 7
       list front --> 13 8 5 3  2 1 1 0
    */
    lnode_t* list = lnode_new((void*)&fibs[0]);
    for (int i = 1; i < n; ++i)
    {
        lnode_t* node = lnode_new((void*)&fibs[i]);
        node->next = list;
        list = node;
    }
    return list;
}

static void destroy_list(lnode_t* list)
{
    lnode_t* p = list;
    while (p != NULL)
    {
        lnode_t* q = p->next;
        lnode_free(p);
        p = q;
    }
}

void run_list_tests()
{
    TEST_ADD_FRONT();
    TEST_ADD_END();
    TEST_LOOKUP();
    TEST_DELETE();
}

void TEST_ADD_FRONT()
{
    char msg_size[] = "List size.";
    char msg_content[] = "List content.";

    lnode_t* list = create_list(NFIBS);
    assert(list != NULL);

    list = list_add_front(list, lnode_new((void*)&fibs[NFIBS]));

    long a[NFIBS + 1];
    size_t a_sz = 0;
    for (lnode_t* p = list; p != NULL; p = p->next)
        a[a_sz++] = *(long*)p->data;

    long e[NFIBS + 1] = {21, 13, 8, 5, 3, 2, 1, 1, 0};
    const size_t e_sz = NFIBS + 1;

    ktest_expect_equal((void*)&e_sz, (void*)&a_sz, sizeof(size_t), msg_size);
    ktest_expect_equal((void*)a, (void*)e, sizeof(long) * e_sz, msg_content);

    destroy_list(list);
}

void TEST_ADD_END()
{
    char msg_size[] = "List size.";
    char msg_content[] = "List content";
    
    lnode_t* list = create_list(NFIBS);
    assert(list != NULL);

    list = list_add_end(list, lnode_new((void*)&fibs[NFIBS]));

    long end_a[NFIBS + 1];
    size_t end_a_sz = 0;
    for (lnode_t* p = list; p != NULL; p = p->next)
       end_a[end_a_sz++] = *(long*)p->data;
    
    long end_e[NFIBS + 1] = {13, 8, 5, 3, 2, 1, 1, 0, 21};
    const size_t end_e_sz = NFIBS + 1;

    ktest_expect_equal((void*)&end_a_sz, (void*)&end_e_sz, sizeof(size_t), msg_size);
    ktest_expect_equal((void*)end_a, (void*)end_e, sizeof(long) * end_e_sz, msg_content);

    destroy_list(list);
}

void TEST_LOOKUP()
{
    char msg_ret[]   = "Return value.";
    char msg_index[] = "Node index.";
    char msg_data[]  = "Node data.";
    
    lnode_t* list = create_list(NFIBS);
    assert(list != NULL);
    
    size_t a_found_node_index;
    const lnode_t* a_found_node = NULL;   
    bool a_lookup_func_ret = list_lookup(list, (void*)&fibs[(NFIBS / 2) - 1], cmp_long, &a_found_node, &a_found_node_index);

    size_t e_found_node_index = 4;
    bool e_lookup_func_ret = true;
    
    ktest_expect_equal(&e_lookup_func_ret, &a_lookup_func_ret, sizeof(bool), msg_ret);
    ktest_expect_equal(&e_found_node_index, &a_found_node_index, sizeof(long), msg_index);

    long e_found_data_val = 2;
    long a_found_data_val = *(long*)lnode_get_data(a_found_node);
    ktest_expect_equal(&e_found_data_val, &a_found_data_val, sizeof(long), msg_data);

    destroy_list(list);
}

void TEST_DELETE()
{
    char msg_ret[]     = "Return value.";
    char msg_index[]   = "Node index.";
    char msg_data[]    = "Node data.";
    char msg_size[]    = "List size.";
    char msg_content[] = "List content.";

    lnode_t* list = create_list(NFIBS);
    assert(list != NULL);

    size_t a_deleted_node_index;
    const lnode_t* a_deleted_node = NULL;   
    bool a_func_ret = list_delete(list, (void*)&fibs[(NFIBS / 2) - 1], cmp_long, &a_deleted_node, &a_deleted_node_index);

    size_t e_deleted_node_index = 4;
    bool e_func_ret = true;
    
    ktest_expect_equal(&e_func_ret, &a_func_ret, sizeof(bool), msg_ret);
    ktest_expect_equal(&e_deleted_node_index, &a_deleted_node_index, sizeof(long), msg_index);

    long e_deleted_data_val = 2;
    long a_deleted_data_val = *(long*)lnode_get_data(a_deleted_node);
    ktest_expect_equal(&e_deleted_data_val, &a_deleted_data_val, sizeof(long), msg_data);
    
    
    long a[NFIBS - 1];
    size_t a_sz = 0;
    for (lnode_t* p = list; p != NULL; p = p->next)
        a[a_sz++] = *(long*)p->data;

    long e[NFIBS - 1] = {13, 8, 5, 3, 1, 1, 0};
    const size_t e_sz = NFIBS - 1;

    ktest_expect_equal((void*)&e_sz, (void*)&a_sz, sizeof(size_t), msg_size);
    ktest_expect_equal((void*)a, (void*)e, sizeof(long) * e_sz, msg_content);

    destroy_list(list);
}
