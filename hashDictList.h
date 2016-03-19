/*
 * By:Samuel Reha  and  Patrick Russell
 *    sreha@ucsc.edu || pcrussel@ucsc.edu
 * Created: 5/12/2014
 * Last Modified: 5/21/2014
 * 
 * CMPS 101 Spring '14 Programming Assignment 4:
 * 
 * NAME: hashDictList.h
 *
 * PURPOSE: This is the interface for the hashDictList ADT. This is a simple 
 *          doubly-linked list used by the hashDict ADT. This list stores 
 *          string / IntList pairs. 
 *
 * Based on a list originally written by 
 * Samuel Reha and Nico Williams.
 */
# include "myinclude.h"
 
typedef struct HashDictListStruct* HashDictListHndl;

/*** Constructors-Destructors ***/
HashDictListHndl newHashDictList( void );

/* Pre: L has been created with newhashDictList. */
void freeHashDictList(HashDictListHndl* L);
 
 
/* NOTE: all Access functions and Manipulation procedures also have the
   precondition that L has been initialized by newhashDictList() and is not null.
*/
/*** Access functions ***/

/* returns true is list is empty else returns false. */
Boolean hashDictListIsEmpty(HashDictListHndl L);

/* returns true if current == NULL*/
Boolean hashDictListOffEnd(HashDictListHndl L);

/* returns true if current == first and !offEnd() */
Boolean hashDictListAtFirst(HashDictListHndl L);

/* returns true if current == last and !offEnd() */
Boolean hashDictListAtLast(HashDictListHndl L);

/* Returns true if the name is found in the list */
Boolean hashDictListLookUp(HashDictListHndl L, char* someName);

/* return the first element;
   pre: !isEmpty()*/
char* hashDictListGetFirst(HashDictListHndl L);

/* return the last element;
   pre: !isEmpty()*/
char* hashDictListGetLast(HashDictListHndl L);

/* return the current element
   pre: !offEnd()*/
char* hashDictListGetCurrent(HashDictListHndl L);

/*** Manipulation procedures ***/

void hashDictListAppendLibrary(HashDictListHndl L, char* someName, int someValue);

/* delete all elements from the list,
   making it empty.
   Post: isEmpty(), offEnd() are both true */
void hashDictListMakeEmpty(HashDictListHndl L);

/* without changing list order, make the first element the current one.
   Pre: !isEmpty(); 
   Post: !offEnd() */
void hashDictListMoveFirst(HashDictListHndl L);

/* without changing list order, make the last element the current one.
   Pre: !isEmpty();
   Post: !offEnd() */
void hashDictListMoveLast(HashDictListHndl L);

/* move the current marker one element earlier in the list
   Pre: !offEnd();
   Post: offEnd() only if atFirst() was true */
void hashDictListMovePrev(HashDictListHndl L);

/* move the current marker one element later in the list.
   Pre: !offEnd();
   Post: offEnd() only if atLast() was true */
void hashDictListMoveNext(HashDictListHndl L);

/* Inserts new element before first
   Post: !isEmpty(); doesn’t change current element */
void hashDictListInsertAtFront(HashDictListHndl L, char* data);

/* Inserts new element after last one
   Post: !isEmpty(); doesn’t change current element */
void hashDictListInsertAtBack(HashDictListHndl L, char* data);

/* Inserts new element before current one
   Pre: !offEnd();
   Post: !isEmpty(), !offEnd(), !atFirst() */
void hashDictListInsertBeforeCurrent(HashDictListHndl L, char* data);

/* delete the first element.
   Pre: !isEmpty()*/
void hashDictListDeleteFirst(HashDictListHndl L);

/* delete the last element.
   Pre: !isEmpty()*/
void hashDictListDeleteLast(HashDictListHndl L);

/* delete the current element.
   Pre: !isEmpty(), !offEnd();
   Post: offEnd()*/
void hashDictListDeleteCurrent(HashDictListHndl L);

/* delete the current element.
   Pre: !isEmpty(), hashDictListLookUp(L, k) == TRUE;
   Post: L->length--, k is not within L */
void hashDictListDeleteKey(HashDictListHndl L, char* k);

/*** Other operations ***/

/* prints out the list, helpful for debugging
   pre: 
   post: */
void printHashDictList(FILE* out, HashDictListHndl L);

/* prints out data fields of the given name.
   pre: 
   post: */
void printHashDictListNode(FILE* out, HashDictListHndl List, char* nameOfNode);