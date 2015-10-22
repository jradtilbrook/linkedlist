/**
 */

#include <stdlib.h>
#include "boolean.h"


/**
 * The datatype stored in the linked list.
 */
typedef void* LinkedListData;


/**
 * pointer to function that takes pointer to data to free.
 * useful if linkedlist_data requires freeing of internal fields (eg. if struct)
 */
/*
typedef void (*FreeDataFunc)(void*);
*/


/**
 * Struct representing a node within the list.
 */
typedef struct LinkedListNode {
    LinkedListData data;
    struct LinkedListNode *next;
} LinkedListNode;


/**
 * Struct representing a list.
 */
typedef struct LinkedList {
    LinkedListNode *head;
} LinkedList;


/**
 * Create a new empty linked list.
 */
LinkedList* createList(void);


/**
 * Delete an entire list.
 *
 * TODO: use double pointer to allow setting to NULL from inside?
 */
void deleteList(LinkedList *);




/*
 * TODO: the following functions may need to return an error status.
 * perhaps either:
 *  - integer (true/false)
 *  - enum representing error type
 *  - pointer to the new/removed element or NULL on error
 * TODO: do the remove functions free the element or return it for use?
 */



/**
 * Add an element to the start.
 */
void insertStart(LinkedList *, LinkedListData);


/**
 * Delete an element at the start.
 */
void removeStart(LinkedList *);


/**
 * Add an element to the end.
 */
void insertEnd(LinkedList *, LinkedListData);


/**
 * Remove the last element.
 */
void removeEnd(LinkedList *);


/**
 * Insert an element before specified index.
 */
void insertIndex(LinkedList *, unsigned int);


/**
 * Remove an element at the specified index.
 */
void removeIndex(LinkedList *, unsigned int);

/* TODO:
 * Missing functions for:
 *  - finding, by index/start/end
 *  - retrieving(=find and return, leave in list)
 *  - retrieving(=find, return and remove from list)
 */

/*
 * TODO: update readme with desired list functionality:
 * - add to start, end, index
 * - remove from start, end, index -> delete from list
 * - find start, end, index (single function most likely)
 * - ...
 */

