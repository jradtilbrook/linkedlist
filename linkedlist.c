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
 * Add an element to the start.
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

