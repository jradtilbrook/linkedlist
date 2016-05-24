/**
 * @file    linkedlist.c
 * @author  Jarryd Tilbrook
 * @date    23 May 2016
 * @brief   Linked list library source file. Defines functions for the library.
 *          For a more detailed explanation of the library see the README.
 */

#include "linkedlist.h"


LinkedList* createList()
{
    /* allocate memory for the list */
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

    /* if no error in allocating, initialise list contents */
    if (list)
        list->head = NULL;

    return list;
}


int insertTop(LinkedList *list, DataPointer data)
{
    ListNode *top;

    /* if list is NULL return immediately */
    if(!list)
        return FALSE;

    /* allocate memory for the node */
    top = (ListNode *) malloc(sizeof(ListNode));
    /* if memory could not be allocated return immediately */
    if(!top)
        return FALSE;

    /* insert the value */
    top->data = data;

    /* add the node to the start */
    top->next = list->head;
    list->head = top;

    return TRUE;
}


int insertTail(LinkedList *list, DataPointer data)
{
    if(list)
    {
        /* allocate memory for the node */
        ListNode *new = (ListNode *) malloc(sizeof(ListNode));
        /* if memory could not be allocated return immediately */
        if(!new)
            return FALSE;

        new->data = data;
        new->next = NULL;

        /* if list is not empty */
        if(list->head)
        {
            ListNode *tail = list->head;

            /* iterate through to the end */
            while(tail && tail->next)
                tail = tail->next;

            tail->next = new;

            return TRUE;
        }
        else
        {
            list->head = new;
            return TRUE;
        }
    }

    return FALSE;
}


void destroyList(LinkedList *list)
{
    /* if list is not NULL or empty */
    if (list)
    {
        if (list->head)
        {
            /* iterate through list removing the head each time */
            do
                removeTop(list);
            while (list->head);
        }

        /* free list struct */
        free(list);
    }
}


void removeTop(LinkedList *list)
{
    /* if list is not NULL or empty */
    if (list && list->head)
    {
        /* re-arrange the list */
        ListNode *top = list->head;
        list->head = top->next;

        /* free the data that was top */
        free(top->data);
        /* free the node itself */
        free(top);
    }
}


void removeTail(LinkedList *list)
{
    /* if list is not NULL or empty */
    if (list && list->head)
    {
        ListNode *tail = list->head;
        ListNode *previous = tail;

        /* if list has only one node */
        if (list->head->next)
        {
            /* iterate through to the end */
            while(tail && tail->next)
            {
                previous = tail;
                tail = tail->next;
            }


            previous->next = NULL;

            free(tail->data);
            free(tail);
        }
        else /* list length > 1 */
        {
            free(list->head->data);
            free(list->head);
            list->head = NULL;
        }
    }
}


unsigned long listLength(LinkedList *list)
{
    /* if list is not NULL or empty */
    if(list && list->head)
    {
        unsigned long length = 1;

        ListNode *current = list->head;
        while (current->next)
        {
            /* move to the next node and increment the length */
            current = current->next;
            length++;
        }

        return length;
    }

    return 0;
}


DataPointer peekTop(LinkedList *list)
{
    /* if list is not NULL or empty */
    if(list && list->head)
        return list->head->data;

    return NULL;
}


DataPointer peekTail(LinkedList *list)
{
    /* if list is not NULL or empty */
    if(list && list->head)
    {
        ListNode *tail = list->head;
        /* iterate through to the end */
        while(tail && tail->next)
            tail = tail->next;
        return tail->data;
    }

    return NULL;
}
