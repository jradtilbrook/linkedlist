/**
 * @file linkedlist.c
 * @author Jarryd Tilbrook
 * @date
 * @brief File containing datatypes and function prototypes for a linked list
 *        library.
 *
 * TODO: add detailed explanation
 */

#include "linkedlist.h"


/**
 * @brief Create a new empty linked list.
 *
 * Allocates memory for the list and initilise the structures fields. If an
 * allocation error occurs an error is logged to @c stderr (if enabled during
 * compilation).
 *
 * @return A pointer to a new empty linked list or @c NULL on error.
 */
LinkedList* createList()
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

    /* If no error in allocating, initialise list contents */
    if (list)
    {
        list->head = NULL;
    }
#ifdef LOG_ERRORS
    else /* Log error an error */
    {
        fprintf(stderr, "SEVERE: Failed to allocate memory for list.\n");
    }
#endif

    return list;
}


/**
 * @brief Delete the list pointed to by @p list.
 *
 * If not @c NULL the data stored in @p list is passed to the user defined
 * callback @p freeData for freeing (assuming the data is a @c struct or similar
 * with dynamically allocated contents). Each node in @p list and @p list itself
 * is freed and @p list is set to @c NULL. Pass @c NULL to @p freeData if the
 * data is a simple type, and it will be freed internally.
 *
 * @param list The list to delete.
 * @param freeData The user defined callback to free the data stored in the
 *                 list.
 *
 * TODO: use double pointer to allow setting to NULL from inside?
 * TODO: decide whether to use conditional compilation for function footprint
 */
void deleteList(LinkedList **list, FreeDataFunc freeData)
{
    /* If list is not NULL or empty */
    if (list && *list && (*list)->head)
    {
        /* Iterate through list removing the head each time */
        do
        {
            removeTop(*list, freeData);
        } while ((*list)->head);

        /* Free list and set to NULL */
        free(*list);
        *list = NULL;
    }
#ifdef LOG_ERRORS
    else /* Log an helpful info */
    {
        fprintf(stderr, "INFO: Attempt to delete a NULL list pointer or empty list.\n");
    }
#endif
}


/**
 * @brief Insert @p value at the head of @p list.
 *
 * Allocates a new node in @p list and copies in @p value. If enabled, memory is
 * alocated first before copying the data in.
 *
 * @param list The list to add to.
 * @param value The data to copy into the list.
 * @return Positive integer if no error occured and the list has been modified.
 */
int insertTop(LinkedList *list, LinkedListData value)
{
    int success = FALSE;

    /* If list is not NULL */
    if (list)
    {
        /* Allocate memory for the node */
        LinkedListNode *node = (LinkedListNode *) malloc(sizeof(LinkedListNode));

        /* If no error, proceed to add node to list */
        if (node)
        {
            /* Allocate memory for the data */
            node->data = (LinkedListData *) malloc(sizeof(LinkedListData));

            /* If no error, add data to node and node to list */
            if (node->data)
            {
                success = TRUE;
                *(node->data) = value; /* copy in the data */
                node->next = list->head; /* add the node to the start */
                list->head = node;
            }
            else /* Free the node memory, and log an error */
            {
                free(node);
#ifdef LOG_ERRORS
                fprintf(stderr, "SEVERE: Failed to allocate memory for data in list.\n");
#endif
            }
        }
#ifdef LOG_ERRORS
        else /* Log an error */
        {
            fprintf(stderr, "SEVERE: Failed to allocate memory for a node in list.\n");
        }
#endif
    }
#ifdef LOG_ERRORS
    else /* Log an helpful info */
    {
        fprintf(stderr, "INFO: Attempt to add to a NULL list pointer.\n");
    }
#endif

    return success;
}


/**
 * @brief Delete the element at the start of @p list.
 *
 * If it exists, the top element in @p list is removed. If required, the user
 * can specifiy a callback to free the data stored in the list, otherwise pass
 * @c NULL to @p freeData and it is freed internally.
 *
 * @param list The list to remove from.
 * @param freeData The user defined callback to free the data stored in the
 *                 list.
 */
void removeTop(LinkedList *list, FreeDataFunc freeData)
{
    /* If list is not NULL or empty */
    if (list && list->head)
    {
        /* Re-arrange the list */
        LinkedListNode *node = list->head;
        list->head = node->next;

        /* Free the data that was top */
        if (freeData)
        {
            (*freeData)(node->data);
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
