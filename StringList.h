/*
 * By: Samuel Reha  and  Patrick Russell
 *       sreha@ucsc.edu ||  pcrussel@ucsc.edu
 * 
 * Last Modified: 5/22/2014
 *
 * CMPS 101 Spring '14 Programming Assignment 4
 *
 * NAME: StringList.h
 *
 * PURPOSE: This header implements the interface defined in List.c. List is a 
 *          simple linked-list based list.
 */

typedef struct IntListStruct* IntListHndl;

/*** Constructors-Destructors ***/

IntListHndl newIntList( void );


void freeIntList(IntListHndl* L);
/* Pre: L has been created with newIntList. */
 
 
/* NOTE: all Access functions and Manipulation procedures also have the
 * precondition that L has been initialized by newIntList().
 */
/*** Access functions ***/

/* returns true is list is empty else returns false.
 * PRE: List != NULL 
 */
Boolean isEmpty(IntListHndl L);

/* returns true if current == NULL
 * PRE: List != NULL 
 */
Boolean offEnd(IntListHndl L);

/* returns true if current == first and !offEnd()
 *  PRE: List != NULL 
 */
Boolean atFirst(IntListHndl L);

/* returns true if current == last and !offEnd()
 * PRE: List != NULL 
 */
Boolean atLast(IntListHndl L);

/* return the first element; 
 * pre: !isEmpty()
 */
int getFirst(IntListHndl L);

/* return the last element; 
 * pre: !isEmpty()
 */
int getLast(IntListHndl L);

/* return the current element 
 * pre: !offEnd()
 */
int getCurrent(IntListHndl L);

/*** Manipulation procedures ***/

/* Delete all elements from the list,
 * making it empty. 
 * Post: isEmpty(), offEnd() are both true
 */
void makeEmpty(IntListHndl L);

/* Without changing list order, make the first element
 * the current one. 
 * Pre: !isEmpty(); Post: !offEnd()
 */
void moveFirst(IntListHndl L);

/* Without changing list order, make the last element 
 * the current one. Pre: !isEmpty(); Post: !offEnd()
 */
void moveLast(IntListHndl L);

/* Move the current marker one element earlier in the list
 * Pre: !offEnd(); Post: offEnd() only if atFirst() was true
 */
void movePrev(IntListHndl L);

/* Move the current marker one element later in the list.
 * Pre: !offEnd(); Post: offEnd() only if atLast() was true
 */
void moveNext(IntListHndl L);

/* Inserts new element before first
 * Post: !isEmpty(); doesn’t change current element
 */
void insertAtFront(IntListHndl L, int data);

/* Inserts new element after last one
 * Post: !isEmpty(); doesn’t change current element
 */
void insertAtBack(IntListHndl L, int data);

/* Inserts new element before current one
 * Pre: !offEnd(); Post: !isEmpty(), !offEnd(), !atFirst()
 */
void insertBeforeCurrent(IntListHndl L, int data);

/* Delete the first element. Pre: !isEmpty()*/
void deleteFirst(IntListHndl L);

/* Delete the last element. Pre: !isEmpty()*/
void deleteLast(IntListHndl L);

/* Delete the current element.
 * Pre: !isEmpty(), !offEnd(); Post: offEnd()
 */
void deleteCurrent(IntListHndl L); 


/*** Other operations ***/

/* Prints out the list with the
 * current element marked, helpful for debugging
 */
void printList(FILE* out, IntListHndl L);
