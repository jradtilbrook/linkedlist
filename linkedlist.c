/**
 */

#include "linkedlist.h"


/**
 * Create a new empty linked list.
 */
LinkedList* createList(void)
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    /*
     * If no error in allocating, initialise list contents.
     */
    if (list)
        list->head = NULL;

    return list;
}


/**
 * Delete an entire list.
 *
 * TODO: use double pointer to allow setting to NULL from inside?
 */
void deleteList(LinkedList *list)
{
    LinkedListNode *current, *next;
    current = list->head;
    next = current;
    while (next)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}


/**
 * Add an element to the start.
 *
 * Precondition: list is a valid pointer
 */
void insertStart(LinkedList *list, LinkedListData data)
{
    LinkedListNode *node = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    /*
     * If no error, proceed to add node to list.
     */
    if (node)
    {
        node->data = data;
        node->next = list->head;
        list->head = node;
    }
}


/**
 * Delete an element at the start.
 *
 * Precondition: list is a valid pointer
 */
void removeStart(LinkedList *list)
{
    if (list->head)
    {
        LinkedListNode *node = list->head;
        list->head = node->next;
        free(node);
    }
}

