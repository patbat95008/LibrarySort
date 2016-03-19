/*
 * By: Samuel Reha  and  Patrick Russell
 *     sreha@ucsc.edu || pcrussel@ucsc.edu
 * 
 * Created: 4/3/2014
 * Last Modified: 5/14/2014
 * 
 * CMPS 101 Spring '14 Programming Assignment 4
 *
 * NAME: IntList.h
 * 
 * PURPOSE: This is the interface for the IntList ADT. List is a simple doubly 
 *          linked-list based list that holds strings.
 */
# include "myinclude.h"
 
typedef struct IntListStruct* IntListHndl;

/*** Constructors-Destructors ***/
IntListHndl newIntList( void );

/* Pre: L has been created with newIntList. */
void freeIntList(IntListHndl* L);
 
 
/* NOTE: all Access functions and Manipulation procedures also have the
   precondition that L has been initialized by newIntList() and is not null.
*/
/*** Access functions ***/

/* returns true is list is empty else returns false. */
Boolean intListIsEmpty(IntListHndl L);

/* returns true if current == NULL*/
Boolean intListOffEnd(IntListHndl L);

/* returns true if current == first and !offEnd() */
Boolean intListAtFirst(IntListHndl L);

/* returns true if current == last and !offEnd() */
Boolean intListAtLast(IntListHndl L);

/* return the first element;
   pre: !isEmpty()*/
int intListGetFirst(IntListHndl L);

/* return the last element;
   pre: !isEmpty()*/
int intListGetLast(IntListHndl L);

/* return the current element
   pre: !offEnd()*/
int intListGetCurrent(IntListHndl L);

/*** Manipulation procedures ***/

/* delete all elements from the list,
   making it empty.
   Post: isEmpty(), offEnd() are both true */
void intListMakeEmpty(IntListHndl L);

/* without changing list order, make the first element the current one.
   Pre: !isEmpty(); 
   Post: !offEnd() */
void intListMoveFirst(IntListHndl L);

/* without changing list order, make the last element the current one.
   Pre: !isEmpty();
   Post: !offEnd() */
void intListMoveLast(IntListHndl L);

/* move the current marker one element earlier in the list
   Pre: !offEnd();
   Post: offEnd() only if atFirst() was true */
void intListMovePrev(IntListHndl L);

/* move the current marker one element later in the list.
   Pre: !offEnd();
   Post: offEnd() only if atLast() was true */
void intListMoveNext(IntListHndl L);

/* Inserts new element before first
   Post: !isEmpty(); doesn’t change current element */
void intListInsertAtFront(IntListHndl L, int data);

/* Inserts new element after last one
   Post: !isEmpty(); doesn’t change current element */
void intListInsertAtBack(IntListHndl L, int data);

/* Inserts new element before current one
   Pre: !offEnd();
   Post: !isEmpty(), !offEnd(), !atFirst() */
void intListInsertBeforeCurrent(IntListHndl L, int data);

/* delete the first element.
   Pre: !isEmpty()*/
void intListDeleteFirst(IntListHndl L);

/* delete the last element.
   Pre: !isEmpty()*/
void intListDeleteLast(IntListHndl L);

/* delete the current element.
   Pre: !isEmpty(), !offEnd();
   Post: offEnd()*/
void intListDeleteCurrent(IntListHndl L); 

/*** Other operations ***/

/* prints out the list with the
   current element marked, helpful for debugging */
void printIntList(FILE* out, IntListHndl L);