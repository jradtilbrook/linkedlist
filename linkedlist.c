/**
 * @file linkedlist.c
 * @author Jarryd Tilbrook
 * @date    25 Mar 2016
 * @brief   Linked list library source file. Defines functions for the library.
 *          For a more detailed explanation of the library see the README.
 */

#include "linkedlist.h"


/**
 * @brief Create a new empty linked list.
 *
 * Allocates memory for the list and initilises the `struct`s fields. Returns
 * `NULL` if an error occurs in memory allocation.
 *
 * @return A pointer to a new empty linked list or `NULL` on error.
 */
LinkedList* createList(FreeDataFunc freeData, DifferenceFunc diff)
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

    /* if no error in allocating, initialise list contents */
    if (list)
    {
        list->head = NULL;
        list->diff = diff;
        list->free = freeData;
    }
#ifdef LOG_ERRORS
    else /* log error an error */
    {
        fprintf(stderr, "SEVERE: Failed to allocate memory for list.\n");
    }
#endif

    return list;
}


/**
 * @brief Insert a value at the top of a list.
 *
 * This expects @p value to be a valid pre-allocated pointer as no checks are
 * performed. This @p value is inserted at the head of the list.
 *
 * @param list The list to add to.
 * @param value The data to copy into the list.
 * @return Positive integer for successful insertion, zero otherwise.
 */
int insertTop(LinkedList *list, LinkedListData value)
{
    LinkedListNode *node;

    /* if list is NULL return immediately */
    if(!list)
        /* log message? */
        return FALSE;

    /* allocate memory for the node */
    node = (LinkedListNode *) malloc(sizeof(LinkedListNode));

    /* if memory could not be allocated return immediately */
    if(!node)
        /* log message? */
        return FALSE;

    /* insert the value */
    node->data = value;

    /* add the node to the start */
    node->next = list->head;
    list->head = node;

    return TRUE;
}


/**
 * @brief Delete an entire list.
 *
 * Frees the entire contents of the linked list @p list by recursively removing
 * the top node.
 *
 * @param list The list to delete.
 */
void destroyList(LinkedList *list)
{
    /* if list is not NULL or empty */
    if (list)
    {
        if (list->head)
        {
            /* iterate through list removing the head each time */
            do
            {
                removeTop(list);
            } while (list->head);
        }

        /* free list and set to NULL */
        free(list);
    }
#ifdef LOG_ERRORS
    else /* log an helpful info */
    {
        fprintf(stderr, "INFO: Attempt to delete a NULL list pointer or empty "
            "list.\n");
    }
#endif
}


/**
 * @brief Delete the element at the start of a list.
 *
 * If it exists, the top element in @p list is removed. This delegates to the
 * function pointer field, `free`, stored in @p list to do the deallocation. If
 * this field is `NULL` the standard implementation of `free()` will be used. If
 * you wish to perform extra checks or if the data stored in the list requires
 * more than a single call to `free()`, ensure that you define an appropriate
 * function.
 *
 * @param list The list to remove from.
 */
void removeTop(LinkedList *list)
{
    /* if list is not NULL or empty */
    if (list && list->head)
    {
        /* Re-arrange the list */
        LinkedListNode *node = list->head;
        list->head = node->next;

        /* Free the data that was top */
        if (list->free)
        {
            (list->free)(node->data);
        }
        else
        {
            free(node->data);
        }

        /* Free the node itself */
        free(node);
    }
#ifdef LOG_ERRORS
    else /* Log an helpful info */
    {
        fprintf(stderr, "INFO: Attempt to remove from a NULL list pointer or empty list.\n");
    }
#endif
}


/**
 * @brief Calculate the length of a list.
 *
 * If it has been enabled this may merely return the length field of @p list.
 * Otherwise the list is traversed to calculate the length.
 *
 * @param list The list to determine the length of.
 * @return The size of the supplied list.
 */
unsigned long listLength(LinkedList *list)
{
    if(list && list->head)
    {
        unsigned long length = 1;

        LinkedListNode *n = list->head;
        while (n->next)
        {
            n = n->next;
            length++;
        }

        return length;
    }
    else
        return 0;
}


/**
 * @brief Retrieves, but does not remove, the element at the start of a list.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the first element, or `NULL` if empty.
 */
LinkedListData peekTop(LinkedList *list)
{
    if(list)
        return list->head;

    return NULL;
}


/**
 * @brief Retrieves, but does not remove, the element at the end of a list.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the last element, or `NULL` if empty.
 */
LinkedListData peekTail(LinkedList *list)
{
    if(list)
    {
        LinkedListNode *current = list->head;
        /* iterate through to the end */
        while(current && current->next)
            current = current->next;
        return current;
    }

    return NULL;
}
