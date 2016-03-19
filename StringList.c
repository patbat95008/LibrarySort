/*
 * By: Samuel Reha  and  Patrick Russell
 *       sreha@ucsc.edu ||  pcrussel@ucsc.edu
 * 
 * Last Modified: 5/22/2014
 *
 * CMPS 101 Spring '14 Programming Assignment 4
 *
 * NAME: StringList.c
 *
 * PURPOSE: This ADT implements the interface defined in List.h. List is a 
 *                   simple linked-list based list.
 */

#include "myinclude.h"
#include "List.h"
#include <assert.h>

/*** type definitions ***/
typedef struct NodeStruct* NodePtr;

typedef struct IntListStruct {
  int Length;
  NodePtr first;
  NodePtr last;
  NodePtr current;
} IntListStruct;

typedef struct NodeStruct {
  int data;
  struct NodeStruct* next;
  struct NodeStruct* prev;
} NodeStruct;


/*** Constructors-Destructors ***/

/* makes a new list */
IntListHndl newIntList (){
  IntListHndl tempList = malloc ( sizeof(IntListStruct) );
  assert(tempList != NULL);
  
  tempList->Length = 0;
  tempList->current = NULL;
  tempList->first = NULL;
  tempList->last = NULL;
  
  return (tempList);
}  

/* frees a given list */
/* PRE: list != NULL */
void freeIntList (IntListHndl *List){
  assert ((*List) != NULL && List != NULL); 
  while (! isEmpty((*List))) {
    deleteLast(*List); 
  }
  free (*List);
  *List = NULL;
}

/* makes a new node */
NodePtr newNode(int someData) {
	NodePtr tempNode = malloc(sizeof(NodeStruct));
	assert(tempNode != NULL);
	
	tempNode->data = someData;
	tempNode->next = NULL;
	tempNode->prev = NULL;
	return(tempNode);
}

/* frees a given node */
/* PRE: Node != NULL */
void freeNode(NodePtr *Node) {
	assert(*Node != NULL && Node != NULL);
	free(*Node);
	*Node = NULL;
	
}
  
/*** Access functions ***/

/* Checks to see if a given list is empty */
/* PRE: List != NULL */
Boolean isEmpty(IntListHndl List){
   assert (List != NULL);

   return (List->Length == 0);
}

/* Checks to see if a given list is off the end */
/* PRE: List != NULL */
Boolean offEnd(IntListHndl List) {
  assert(List != NULL);
  
  return (List->current == NULL);
}

/* Checks to see if a given list is at the 
 * first node in the list
 * PRE: List != NULL
 */
Boolean atFirst(IntListHndl List) {
  assert (List != NULL);
  
  return (List->current == List->first && !offEnd(List));
}

/* Checks to see if a given list is at the 
 * last node in the list
 * PRE: List != NULL
 */
Boolean atLast(IntListHndl List) {
  assert (List != NULL);
  
  return (List->current == List->last && !offEnd(List));
}

/* Gets the first element in the list */
/* PRE: List != NULL, List isn't empty */
int getFirst(IntListHndl List) {
  assert (List != NULL);
  assert (!isEmpty(List));
  
  return (List->first->data);
}

/* Gets the last element in the list */
/* PRE: List != NULL, List isn't empty */
int getLast(IntListHndl List) {
  assert (List != NULL);
  assert (!isEmpty(List));
  
  return (List->last->data);
}

/* gets the current element in the list */
/* PRE: List != NULL, List isn't empty, 
 *                    Current element != NULL
 */
int getCurrent(IntListHndl List) {
  assert (List != NULL);
  assert (!isEmpty(List));
  assert (List->current != NULL);
  
  return (List->current->data);
}

/*** Manipulation procedures ***/

/* Makes the list empty. */
void makeEmpty(IntListHndl List){
  while(List->Length > 0){
    deleteFirst(List);
  }
  assert(isEmpty(List));
  assert(offEnd(List));
}

/* Moves the current element to the head */
/* PRE: list isn't empty */
void moveFirst(IntListHndl List){
  assert(!isEmpty(List));
  
  List->current = List->first;
}

/* Moves the current element to the rear */
/* PRE: list isn't empty */
void moveLast(IntListHndl List){
  assert(!isEmpty(List));
  
  List->current = List->last;
}

/* Moves the current element back one in the list */
/* PRE: current isn't off the end of the list */
void movePrev(IntListHndl List){
  assert(!offEnd(List));
  
  List->current = List->current->prev;
}

/* Moves the current element one further */
/* PRE: current isn't off the end of the list */
void moveNext(IntListHndl List){
  assert(!offEnd(List));
  
  List->current = List->current->next;
}

/* Inserts an element at the front of the list */
void insertAtFront(IntListHndl List, int data){
  assert (List != NULL);
  
  NodePtr tmp = newNode(data);
  if (isEmpty(List)) {
    List->first = tmp;
    List->current = tmp;
    List->last = tmp;
  } else {
    tmp->next = List->first;
    List->first->prev = tmp;
    List->first = tmp;
  }
  List->Length++;
}

/* Inserts an element at the rear of the list */
void insertAtBack(IntListHndl List, int data){
  assert (List != NULL);
  
  NodePtr tmp = newNode(data);
  if (isEmpty(List)) {
    List->first = tmp;
    List->current = tmp;
    List->last = tmp;
  } else {
    tmp->prev = List->last;
    List->last->next = tmp;
    List->last = tmp;
  }
  List->Length++;
}

/* Inserts an element before the current element */
/* PRE:  Current isn't off the end of the list */
void insertBeforeCurrent(IntListHndl List, int data){
  assert(!offEnd(List));
  assert(List != NULL);
   
  if ((List->current) == (List->first)) {
    insertAtFront(List, data);
  } else {
    NodePtr tmp = newNode(data);
    tmp->next=List->current;
	tmp->prev=List->current->prev;
	List->current->prev=tmp;
	tmp->prev->next=tmp;
	List->Length++;
  }

}
 /* Deletes the first element in the list, moves up everything */
 /* PRE: List isn't empty */
void deleteFirst(IntListHndl List){
  assert (List != NULL);
  assert (!isEmpty(List));
  
  if (List->Length == 1) {
    assert(List->first != NULL);
	freeNode(&List->first);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
  } else {
    if((List->first) == (List->current)){
	  NodePtr tmp = List->first;
      NodePtr tmp2 = tmp->next;
      tmp->next = NULL;
      tmp2->prev = NULL;
      List->first = tmp2;
      freeNode(&tmp);
      tmp = NULL;
	  List->current = NULL;
	}else{
      NodePtr tmp = List->first;
      NodePtr tmp2 = tmp->next;
      tmp->next = NULL;
      tmp2->prev = NULL;
      List->first = tmp2;
      freeNode(&tmp);
      tmp = NULL;
	}
  }
  List->Length--;
}

/* Deletes the last element in the list */
/* PRE: List isn't empty */
void deleteLast(IntListHndl List){
  assert (List != NULL);
  assert (!isEmpty(List));
  
  if (List->Length == 1) {
	freeNode(&List->last);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
  } else {
    if((List->last) == (List->current)){
      NodePtr tmp = List->last;
      NodePtr tmp2 = tmp->prev;
      tmp->prev = NULL;
      tmp2->next = NULL;
      List->last = tmp2;
      freeNode(&tmp);
      tmp = NULL;
	  List->current = NULL;
	}else{
	  NodePtr tmp = List->last;
      NodePtr tmp2 = tmp->prev;
      tmp->prev = NULL;
      tmp2->next = NULL;
      List->last = tmp2;
      freeNode(&tmp);
      tmp = NULL;
	}
  }
  List->Length--;
}

/* deletes the current element, sets Current to NULL */
/* PRE: List isn't empty, Current is on the list */
void deleteCurrent(IntListHndl List){
  assert (List != NULL);
  assert (!isEmpty(List));
  assert (!offEnd(List));
  
  if (List->Length == 1) {
    freeNode(&List->first);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
	List->Length--;
  } else {
    if (atFirst(List)) {
      deleteFirst(List);
      List->current = NULL;
    } else if (atLast(List)) {
      deleteLast(List);
      List->current = NULL;
    } else {
      List->current->prev->next = List->current->next;
      List->current->next->prev = List->current->prev;
      freeNode(&List->current);
      List->current = NULL;
	  List->Length--;
    }
  }  

}

/*** Other operations ***/

/* debug, prints all the elements in the list */
/* PRE: List isn't empty */
void printList(FILE* out, IntListHndl List){
  assert (List != NULL);
  assert (!isEmpty(List));

  NodePtr tmp = List->first;
  while (tmp != NULL){
    if (tmp == List->current){
      printf("{%li} ",tmp->data);
    } else {
      printf("%li ", tmp->data);
    }
    tmp = tmp->next;
  }
  printf("\n");
}