/**
 * @file linkedlist.h
 * @author Jarryd Tilbrook
 * @date
 * @brief File containing datatypes and function prototypes for a linked list
 *        library.
 *
 * TODO: add detailed explanation
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
/* The macros below allow the user to modify the behaviour of the list.
 * Uncomment as desired. */

/**
 * This enables the length of the list to be instantly accessible from the list
 * @c struct, as opposed to being calculated by traversing the list.
 */
/*#define INSTANT_LENGTH*/

/**
 * This enables a double ended linked list @c struct.
 */
/*#define DOUBLE_ENDED*/

/**
 * This enables a doubly linked linked list @c struct.
 */
/*#define DOUBLY_LINKED*/

/**
 * This enables logging information to be printed to @c stderr.
 */
/*#define LOG_ERRORS*/

#ifdef LOG_ERRORS
/**
 * If logging is enabled, this will enable a colourised output.
 */
/*#define COLOURISE_ERRORS*/
#endif




/***** DATATYPE DEFINITIONS *****/
/* This section defines the datatypes used within the list, ranging from the
 * <tt>struct</tt>s to the function callback types. */

/**
 * The datatype stored in the linked list. Change to whatever the application
 * calls for.
 * <b>Note:</b> The current implementation will not allow for simultaneous lists
 * that store different datatypes.
 */
typedef char LinkedListData;


/**
 * A @c struct representing a node within the list.
 */
typedef struct LinkedListNode {
    LinkedListData *data;
    struct LinkedListNode *next;
} LinkedListNode;


/**
 * A @c struct representing a list.
 */
typedef struct LinkedList {
    LinkedListNode *head;
} LinkedList;


/**
 * A @c struct representing an array of the same data stored in a list.
 */
typedef struct ArrayList {
    LinkedListData *item; /* or element? */
    unsigned int length;
} ArrayList;


/**
 * @brief A function pointer type that takes a pointer to the type stored in the
 * 		  list.
 *
 * The user can define a function of this type that is used to free non-standard
 * data when deleting an element or the entire list. eg: freeing the contents of
 * a dynamically allocated struct.
 */
typedef void (* FreeDataFunc)(LinkedListData *);


/**
 * @brief A function pointer type that takes two values of the type stored in
 *        the list.
 *
 * The user can define a function of this type that is used to compare two
 * elements from a list that cannot be used in a boolean expression directly.
 * The defined function should return TRUE if the two elements are deemed
 * equivalent.
 */
typedef int (* CompareFunc)(LinkedListData, LinkedListData);




/***** INSERTION & CREATION FUNCTIONS *****/
/* The functions below provide methods of creating a new list and inserting
 * elements at specific positions. A converter function is also provided that
 * performs linked list to array conversion to decrease access times. */

/**
 * @brief Create a new empty linked list.
 *
 * Allocates memory for the list and initilise the structures fields. If an
 * allocation error occurs an error is logged to @c stderr (if enabled during
 * compilation).
 *
 * @return A pointer to a new empty linked list or @c NULL on error.
 */
LinkedList* createList();


/**
 * @brief Convert a linked list into an array.
 *
 * Creates an array from the elements stored in @p list to reduce access times.
 * It leaves the ordering of contents as is (ie. head is first element in the
 * array). The nodes within @p list and the @p list itself are freed. If an
 * allocation error occurs, the list is left unmodified and @c NULL is returned.
 *
 * @param list The list to convert, containing the data to include in the
 *             array.
 * @return A pointer to a new @c ArrayList structure containing the elements and
 *         the length.
 */
ArrayList* list2Array(LinkedList **list);


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
int insertTop(LinkedList *list, LinkedListData value);


/**
 * @brief Insert @p value at the end of @p list.
 *
 * Allocates a new node in @p list and copies in @p value. If enabled, memory is
 * alocated first before copying the data in.
 *
 * @param list The list to add to.
 * @param value The data to copy into the list.
 * @return Positive integer if no error occured and the list has been modified.
 */
int insertTail(LinkedList *list, LinkedListData value);


/**
 * @brief Insert @p value into @p list at @p index.
 *
 * Allocates a new node in @p list and copies in @p value. If enabled, memory is
 * alocated first before copying the data in.
 *
 * @param list The list to add to.
 * @param value The data to copy into the list.
 * @param index The index to insert at (starting at 0).
 * @return Positive integer if no error occured and the list has been modified.
 */
int insertIndex(LinkedList *list, LinkedListData value, unsigned int index);




/***** REMOVAL & DELETION FUNCTIONS *****/
/* The functions below provide methods to remove elements from a list, or delete
 * an entire list itself. */

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
void deleteList(LinkedList **list, FreeDataFunc freeData);


/**
 * @brief Delete the array pointed to by @p array.
 *
 * If not @c NULL the data stored in @p array is passed to the user defined
 * callback @p freeData for freeing (assuming the data is a @c struct or similar
 * with dynamically allocated contents). @p array itself is then freed and set
 * to @c NULL. Pass @c NULL to @p freeData if the data is a simple type, and it
 * will be freed internally.
 *
 * @param array The array to delete.
 * @param freeData The user defined callback to free the data stored in the
 *                 list.
 * @return Positive integer if no error occured and the list has been modified.
 *
 * TODO: use double pointer to allow setting to NULL from inside?
 */
int deleteArray(ArrayList **array, FreeDataFunc freeData);


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
void removeTop(LinkedList *list, FreeDataFunc freeData);


/**
 * Remove the last element.
 */
/**
 * @brief Delete the element at the end of @p list.
 *
 * If it exists, the tail element in @p list is removed. If required, the user
 * can specifiy a callback to free the data stored in the list, otherwise pass
 * @c NULL to @p freeData and it is freed internally.
 *
 * @param list The list to remove from.
 * @param freeData The user defined callback to free the data stored in the
 *                 list.
 * @return Positive integer if no error occured and the list has been modified.
 */
int removeTail(LinkedList *list, FreeDataFunc freeData);


/**
 * Remove an element at the specified index.
 */
/**
 * @brief Delete the element at @p index within @p list.
 * @param list The list to remove from.
 * @param index The index to remove (starting from 0).
 * @param freeData The user defined callback to free the data stored in the
 *                 list.
 * @return Positive integer if no error occured and the list has been modified.
 */
int removeIndex(LinkedList *list, unsigned int index, FreeDataFunc freeData);




/***** FINDING & SEARCHING FUNCTIONS *****/
/* The functions below will not modify the linked list in any way. They are used
 * to obtain information about the list, eg; the length, whether a specific
 * element is present and retrieving a specific element. */

/**
 * @brief Calculate the length of @p list.
 *
 * If it has been enabled this may merely return the size field of the list.
 * Otherwise the list is traversed to calculate the length.
 *
 * @param list The list to determine the length of.
 * @return The size of the supplied list, or -1 on error.
 */
long listLength(LinkedList *list);


/**
 * @brief Find whether @p needle is present in @p list.
 *
 * This function traverses @p list checking whether at least one element is
 * present that is equivalent to @p needle. If the datatype stored in the list
 * is invalid for boolean operations the user must specify a callback which will
 * be passed @p needle, and each element in @p list, and return @c TRUE if They
 * are deemed equivalent. Pass @c NULL to @p compare if this is not required
 * and the data will be checked internally.
 *
 * @param list The list to search through.
 * @param needle The element to search for.
 * @param compare The user defined callback to test for equality.
 * @return @c TRUE if at least one equal element was found.
 * TODO: return index of element (or -1), or return pointer to it (or NULL)
 */
int findElement(LinkedList *list, LinkedListData needle, CompareFunc compare);


/**
 * @brief Retrieves, but does not remove, the element at the start of @p list.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the first element, or @c NULL if empty.
 */
LinkedListData * peekTop(LinkedList *list);


/**
 * @brief Retrieves, but does not remove, the element at the end of @p list.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the last element, or @c NULL if empty.
 */
LinkedListData * peekTail(LinkedList *list);


/**
 * @brief Retrieves, but does not remove, the element at @p index of @p list.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the element, or @c NULL if out of bounds.
 */
LinkedListData * peekIndex(LinkedList *list, unsigned int index);


 #endif /* end of include guard: LINKEDLIST_H */
