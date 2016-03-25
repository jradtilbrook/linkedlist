/**
 * @file    linkedlist.h
 * @author  Jarryd Tilbrook
 * @date    25 Mar 2016
 * @brief   Linked list library header file. Declares the public functions and
 *          datatypes accessible to the end user. For a more detailed
 *          explanation of the library see the README.
 */


#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <stdlib.h>
#include <stdio.h>


/* TRUE/FALSE values for C89 */
#ifndef FALSE
    #define FALSE 0
#endif
#ifndef TRUE
    #define TRUE !FALSE
#endif


/***** CONDITIONAL COMPILATION *****/
/* The macros below allow the user to modify the behaviour of the list as
 * compile time.
 * Uncomment as desired. */

/**
 * This enables the length of the list to be instantly accessible from the list
 * `struct`, as opposed to being calculated by traversing the list.
 */
/*#define INSTANT_LENGTH*/

/**
 * This enables a double ended linked list.
 */
/*#define DOUBLE_ENDED*/

/**
 * This enables a doubly linked linked list.
 */
/*#define DOUBLY_LINKED*/

/**
 * This enables logging information to be printed to `stderr`.
 */
/*#define LOG_ERRORS*/

#ifdef LOG_ERRORS
/**
 * If logging is enabled, this will enable a colourised output.
 */
/*#define COLOURISE_ERRORS*/
/* TODO add logging level macro. Or include a switch at run time when constructing the list */
#endif


/***** DATATYPE DEFINITIONS *****/
/* This section defines the datatypes used within the list, ranging from the
 * `struct`s to the function callback types. */

/**
 * The datatype stored in the linked list. `void` pointer is used to allow for
 * any type to be stored in the list.
 */
typedef void* LinkedListData;


/**
 * @brief A function pointer type that takes a pointer to the type stored in the
 * 		  list and frees the memory pointed to.
 *
 * The user can define a function of this type that is used to free non-standard
 * data when deleting an element or the entire list. eg: freeing the contents of
 * a dynamically allocated `struct`.
 */
typedef void (* FreeDataFunc)(LinkedListData);


/**
 * @brief A function pointer type that takes two values of the type stored in
 *        the list and compares them for equality.
 *
 * The user can define a function of this type that is used to compare two
 * elements from a list that cannot be used in a boolean expression directly.
 * The defined function should return 0 for equal comparison, < 0 if the first
 * argument is less than the second, and > 0 if the first is larger than the
 * second.
 */
typedef int (* DifferenceFunc)(LinkedListData, LinkedListData);


/**
 * @brief A function pointer type that takes a pointer to an item to store in
 *        the list, allocates memory for it, and copies the item across.
 *
 * The user may define a function of this type that will be used to allocate and
 * copy an item into the list. Helps to enforce better modularisation of code.
 * The function should return a pointer to the newly allocated memory, or `NULL`
 * on error.
 */
typedef LinkedListData (* AllocFunc)(LinkedListData);


/**
 * A `struct` representing a node within the list.
 */
typedef struct LinkedListNode {
    LinkedListData data;
    struct LinkedListNode *next;
    #ifdef DOUBLY_LINKED
        struct LinkedListNode *prev;
    #endif
} LinkedListNode;


/**
 * A `struct` representing an array of the same data stored in a list.
 */
typedef struct ArrayList {
    LinkedListData element;
    unsigned long length;
} ArrayList;


/**
 * A `struct` representing a linked list instance. Contains a pointer to the
 * head and pointers to user defined functions used to compare, delete and
 * allocate items within the list. Also optionally contains a pointer to the
 * tail of the list, and the length of the list.
 */
typedef struct LinkedList {
    LinkedListNode *head;
    #ifdef DOUBLE_ENDED
        LinkedListNode *tail;
    #endif
    #ifdef INSTANT_LENGTH
        unsigned long length;
    #endif
    DifferenceFunc diff;
    FreeDataFunc free;
    AllocFunc alloc;
} LinkedList;


/***** INSERTION & MODIFICATION FUNCTIONS *****/
/* The functions below provide methods of creating a new list and inserting
 * elements at specific positions. A converter function is also provided that
 * performs linked list to array conversion to decrease access times. */

/**
 * @brief Create a new empty linked list.
 *
 * Allocates memory for the list and initilises the `struct`s fields. Returns
 * `NULL` if an error occurs in memory allocation.
 *
 * @return A pointer to a new empty linked list or `NULL` on error.
 */
LinkedList* createList(FreeDataFunc free, DifferenceFunc diff);


/**
 * @brief Convert a linked list into an array.
 *
 * Creates an array from the elements stored in @p list to help reduce element
 * access times. The exported array can also be in sorted order by passing a
 * positive value to @p sort. Otherwise, tt leaves the ordering of contents as
 * is. The nodes within @p list and the @p list itself is freed. If an error
 * occurs, the list is left unmodified and `NULL` is returned.
 *
 * @param list The list to convert, containing the data to include in the
 *             array.
 * @return A pointer to a new `ArrayList` structure containing the elements and
 *         the length.
 * TODO: this needs more thinking/designing... ie single 'chunk' of memory, how to allocate -> lists alloc func won't work, array of pointers to list elements?
 */
ArrayList* list2Array(LinkedList *list, int sort);


/**
 * @brief Insert a value at the top of a list.
 *
 * If the list is configured to use an external allocating function, that will
 * be used, and the pointer returned will be stored in the list, otherwise it
 * will assume the data passed in is pre-allocated.
 *
 * @param list The list to add to.
 * @param value The data to copy into the list.
 * @return Positive integer for successful insertion, zero otherwise.
 */
int insertTop(LinkedList *list, LinkedListData value);


/**
 * @brief Insert a value at the end of a list.
 *
 * Similar to insertTop(), but will add the element to the end of @p list.
 *
 * @param list The list to add to.
 * @param value The data to insert into the list.
 * @return Positive integer for successful insertion, zero otherwise.
 */
int insertTail(LinkedList *list, LinkedListData value);


/**
 * @brief Insert a value into a list at a given index.
 *
 * If configured, the user defined allocation function will be used to allocate
 * memory for @p value and add it to the list, otherwise it is assumed that
 * @p value is pre-allocated. After excecution, @p value will be at @p index
 * within the list. Note that negative indexing is supported.
 *
 * @param list The list to add to.
 * @param value The data to insert into the list.
 * @param index The index to insert at (starting at 0).
 * @return Positive integer for successful insertion, zero otherwise. (eg.
 *         index out of bounds)
 */
int insertIndex(LinkedList *list, LinkedListData value, long index);


/**
 * @brief Insert a value in sorted order into the list.
 *
 * Using the defined difference function field in @p list, inserts @p value in
 * sorted order into the list. If the field is `NULL`, @p value will be inserted
 * at the top of the list and a negative integer returned.
 *
 * @param  list  The list to add to.
 * @param  value The data to insert into the list.
 * @return Positive integer for successful insertion, negative if no sort
 *         function was used, and zero otherwise.
 */
int insertSorted(LinkedList *list, LinkedListData value);


/**
 * @brief Sorts a list inplace using a difference function.
 *
 * Sorts @p list inplace using either the defined difference function field in
 * @p list, or another difference function passed in to @p compare. Use this
 * parameter to override the existing difference function.
 *
 * @param  list    The list to sort.
 * @param  diff The overriding compare function to use to determine ordering.
 */
void sortList(LinkedList *list, DifferenceFunc diff);


/***** REMOVAL & DELETION FUNCTIONS *****/
/* The functions below provide methods to remove elements from a list, or delete
 * an entire list itself. */

/**
 * @brief Delete an entire list.
 *
 * Frees the entire contents of the linked list @p list. Delegates to the `free`
 * field of @p list for deallocation, or if this is `NULL` frees each node
 * internally, followed by the list itself.
 *
 * @param list The list to delete.
 */
void destroyList(LinkedList *list);


/**
 * @brief Delete an array converted from a list.
 *
 * Frees the contents of @p array. Delegates freeing to @p freeData to ensure
 * `structs` are properly deallocated. If @p freeData is `NULL` it is freed
 * internally.
 *
 * @param array The array to delete.
 * @param freeData The user defined callback to free the data stored in the
 *                 list.
 */
int destroyArray(ArrayList *array, FreeDataFunc freeData);


/**
 * @brief Delete the element at the start of a list.
 *
 * If it exists, the top element in @p list is removed. Delegates to the `free`
 * field of @p list to ensure all contents of the node are freed. If this field
 * is `NULL` it is freed internally.
 *
 * @param list The list to remove from.
 */
void removeTop(LinkedList *list);


/**
 * @brief Delete the element at the end of a list.
 *
 * If it exists, the last element in @p list is removed. Delegates to the `free`
 * field of @p list to ensure all contents of the node are freed. If this field
 *
 * @param list The list to remove from.
 */
void removeTail(LinkedList *list);


/**
 * @brief Delete the element at a given index within a list.
 *
 * If it exists, the element at @p index is removed from the list. Delegates to
 * the `free` field of @p list to ensure all contents of the node are freed. If
 * this field. Negative indexing is supported.
 *
 * @param list The list to remove from.
 * @param index The index to remove (starting from 0).
 * @return Positive integer for successful removal, zero otherwise.
 */
int removeIndex(LinkedList *list, long index);


/**
 * @brief Remove a node that matches a specified value.
 *
 * Use this to remove an element from @p list that matches @p value. This
 * delegates the comparison to @p diff, or if `NULL` defaults to the difference
 * function pointer stored in @p list. Use this to override the comparison (eg.
 * to loosen the constraints).
 *
 * @param  list    The list to remove from.
 * @param  element The compared element to find and remove.
 * @param  compare The overriding comparison function to use.
 * @return Positive integer for successful removal, zero otherwise.
 */
int removeElement(LinkedList *list, LinkedListData value,
        DifferenceFunc diff);


/***** FINDING & SEARCHING FUNCTIONS *****/
/* The functions below will not modify the linked list in any way. They are used
 * to obtain information about the list, eg; the length, whether a specific
 * element is present and retrieving a specific element. */

/**
 * @brief Calculate the length of a list.
 *
 * If it has been enabled this may merely return the length field of @p list.
 * Otherwise the list is traversed to calculate the length.
 *
 * @param list The list to determine the length of.
 * @return The size of the supplied list.
 */
unsigned long listLength(LinkedList *list);


/**
 * @brief Find whether an element exists in the list.
 *
 * This function traverses @p list checking whether at least one element is
 * present that is equivalent to @p needle. This delegates the comparison to
 * @p diff or the difference function supplied in @p list if `NULL`. @p diff
 * therefore overrides it's counterpart in @p list. This is useful to loosen the
 * comparing constraints on the list elements compared to that used for
 * inserting. Returns a pointer to the first found element or `NULL` if one is
 * not found.
 *
 * @param list The list to search through.
 * @param needle The element to search for.
 * @param diff Overriding comparison function to use.
 * @return A pointer to the found element, or `NULL` if not found.
 */
LinkedListData findElement(LinkedList *list, LinkedListData needle,
        DifferenceFunc diff);


/**
 * @brief Retrieves, but does not remove, the element at the start of a list.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the first element, or `NULL` if empty.
 */
LinkedListData peekTop(LinkedList *list);


/**
 * @brief Retrieves, but does not remove, the element at the end of a list.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the last element, or `NULL` if empty.
 */
LinkedListData peekTail(LinkedList *list);


/**
 * @brief Retrieves, but does not remove, the element at a given index of a
 *        list.
 *
 * Negative indexing is supported.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the element, or `NULL` if out of bounds.
 */
LinkedListData peekIndex(LinkedList *list, long index);


 #endif /* end of include guard: LINKEDLIST_H */
