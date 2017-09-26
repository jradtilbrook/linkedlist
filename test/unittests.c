/**
 * @file    unittests.c
 * @author  Jarryd Tilbrook
 * @date    24 May 2016
 * @brief   Unit testing source code for the linked list library.
 */


#ifndef UNIT_TESTING
    #define UNIT_TESTING 1
#endif
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmocka.h>
#include "../linkedlist.h"

//TODO add comments
static void test_createList(void **state)
{
    LinkedList *list = createList();
    assert_non_null(list);
    assert_null(list->head);
    free(list);
}


static void *reducer(DataPointer data, void *carry)
{
    // if there is a carry value, add the current
    if (carry)
    {
        *(int*)carry += *(int*)data;
    }
    return carry;
}

static void test_reduceList_empty(void **state)
{
    LinkedList *list = createList();

    // when we call the reduceList function on an empty list
    int a = 42;
    int *actual = reduceList(list, &reducer, &a);

    // we expect the seed to be returned
    assert_int_equal(42, *actual);

    destroyList(list);
}


static void test_reduceList_simple(void **state)
{
    LinkedList *list = createList();

    // add in a some test data to the list
    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        insertTail(list, a);
    }

    // when we call the reduceList function
    int *actual = malloc(sizeof(int));
    *actual = 0;
    actual = reduceList(list, &reducer, actual);

    // we expect the correct value
    assert_int_equal(45, *actual);

    free(actual);
    destroyList(list);
}


static void test_destroyList_empty(void **state)
{
    LinkedList *list = createList();
    assert_non_null(list);
    destroyList(list);
    destroyList(NULL);
}


static void test_destroyList(void **state)
{
    LinkedList *list = createList();
    assert_non_null(list);
    insertTop(list, NULL);
    insertTop(list, NULL);
    destroyList(list);
}


static void test_listLength(void **state)
{
    const int l = 1001;
    LinkedList *list = createList();
    assert_non_null(list);
    assert_int_equal(listLength(NULL), 0);
    assert_int_equal(listLength(list), 0);
    for(int i = 0; i < l; i++)
    {
        insertTop(list, malloc(sizeof(char)));
        assert_int_equal(listLength(list), i + 1);
    }
    destroyList(list);
}


static void test_insertTop(void **state)
{
    const int a = 1001;
    LinkedList *list = createList();
    assert_non_null(list);
    assert_false(insertTop(NULL, NULL));
    int b = 0;
    assert_false(insertTop(NULL, &b));
    for (int i = 0; i < a; i++)
    {
        int *c = malloc(sizeof(int));
        assert_true(insertTop(list, c));
        assert_ptr_equal(list->head->data, c);
    }
    destroyList(list);
}


static void test_removeTop(void **state)
{
    const int a = 1001;
    LinkedList *list = createList();
    assert_non_null(list);
    for (int i = 0; i < a; i++)
    {
        insertTop(list, malloc(sizeof(int)));
    }

    assert_int_equal(listLength(list), a);

    for (int i = a; i > 0; i--)
    {
        removeTop(list);
    }

    assert_int_equal(listLength(list), 0);
    destroyList(list);
}


static void test_insertTail(void **state)
{
    const int a = 1001;
    LinkedList *list = createList();
    assert_non_null(list);
    assert_false(insertTail(NULL, NULL));
    int b = 0;
    assert_false(insertTail(NULL, &b));
    for (int i = 0; i < a; i++)
    {
        int *c = malloc(sizeof(int));
        assert_true(insertTail(list, c));
        assert_ptr_equal(peekTail(list), c);
    }
    destroyList(list);
}


static void test_removeTail(void **state)
{
    const int a = 1001;
    LinkedList *list = createList();
    assert_non_null(list);
    for (int i = 0; i < a; i++)
    {
        insertTop(list, malloc(sizeof(int)));
    }

    assert_int_equal(listLength(list), a);

    for (int i = a; i > 0; i--)
    {
        removeTail(list);
    }

    assert_int_equal(listLength(list), 0);
    destroyList(list);
}


static void test_peekTop(void **state)
{
    const int a = 1001;
    LinkedList *list = createList();
    assert_non_null(list);
    for (int i = 0; i < a; i++)
    {
        int *c = malloc(sizeof(int));
        *c = i;
        insertTop(list, c);
        assert_int_equal(*(int*)peekTop(list), i);
    }
    destroyList(list);
}


static void test_peekTail(void **state)
{
    const int a = 1001;
    LinkedList *list = createList();
    assert_non_null(list);
    for (int i = 0; i < a; i++)
    {
        int *c = malloc(sizeof(int));
        *c = i;
        insertTop(list, c);
        assert_int_equal(*(int*)peekTail(list), 0);
    }
    destroyList(list);
}


int main()
{
    /* array of unit tests to run */
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_createList),
        cmocka_unit_test(test_reduceList_empty),
        cmocka_unit_test(test_reduceList_simple),
        cmocka_unit_test(test_destroyList_empty),
        cmocka_unit_test(test_destroyList),
        cmocka_unit_test(test_listLength),
        cmocka_unit_test(test_insertTop),
        cmocka_unit_test(test_removeTop),
        cmocka_unit_test(test_insertTail),
        cmocka_unit_test(test_removeTail),
        cmocka_unit_test(test_peekTop),
        cmocka_unit_test(test_peekTail)
    };

    /* run tests and return number failed */
    return cmocka_run_group_tests(tests, NULL, NULL);
}
