/*
 * By: Samuel Reha  and  Patrick Russell
 *       sreha@ucsc.edu ||  pcrussel@ucsc.edu
 * 
 * Last Modified: 5/20/2014
 *
 * CMPS 101 Spring '14 Programming Assignment 4
 *
 * NAME: IntList.c
 *
 * PURPOSE: This ADT implements the interface defined in List.h. 
 *                   List is a doubly-linked list based list.
 */

# include "myinclude.h"
# include <assert.h>
# include "IntList.h"


typedef struct IntNodeStruct* IntNodePtr;

typedef struct IntListStruct {
  int Length;
  IntNodePtr first;
  IntNodePtr last;
  IntNodePtr current;
} IntListStruct;

typedef struct IntNodeStruct {
  int data;
  struct IntNodeStruct* next;
  struct IntNodeStruct* prev;
} IntNodeStruct;


/*** Constructors-Destructors ***/

IntListHndl newIntList (){
  IntListHndl tempList = malloc ( sizeof(IntListStruct) );
  assert(tempList != NULL);
  
  tempList->Length = 0;
  tempList->current = NULL;
  tempList->first = NULL;
  tempList->last = NULL;
  
  return (tempList);
}  

void freeIntList (IntListHndl *List){
  assert ((*List) != NULL && List != NULL); 
  while (! intListIsEmpty((*List))) {
    intListDeleteLast(*List); 
  }
  free (*List);
  *List = NULL;
}

IntNodePtr newIntNode(int someData) {
	IntNodePtr tempNode = malloc(sizeof(IntNodeStruct));
	assert(tempNode != NULL);
	
	tempNode->data = someData;
	tempNode->next = NULL;
	tempNode->prev = NULL;
	return(tempNode);
}

void freeIntNode(IntNodePtr *Node) {
	assert(*Node != NULL && Node != NULL);
	free(*Node);
	*Node = NULL;
	
}
  
/*** Access functions ***/

Boolean intListIsEmpty(IntListHndl List){
   assert (List != NULL);

   return (List->Length == 0);
}

Boolean intListOffEnd(IntListHndl List) {
  assert(List != NULL);
  
  return (List->current == NULL);
}

Boolean intListAtFirst(IntListHndl List) {
  assert (List != NULL);
  
  return (List->current == List->first && !intListOffEnd(List));
}

Boolean intListAtLast(IntListHndl List) {
  assert (List != NULL);
  
  return (List->current == List->last && !intListOffEnd(List));
}

int intListGetFirst(IntListHndl List) {
  assert (List != NULL);
  assert (!intListIsEmpty(List));
  
  return (List->first->data);
}

int intListGetLast(IntListHndl List) {
  assert (List != NULL);
  assert (!intListIsEmpty(List));
  
  return (List->last->data);
}

int intListGetCurrent(IntListHndl List) {
  assert (List != NULL);
  assert (!intListIsEmpty(List));
  assert (List->current != NULL);
  
  return (List->current->data);
}

/*** Manipulation procedures ***/

void intListMakeEmpty(IntListHndl List){
  while(List->Length > 0){
    intListDeleteFirst(List);
  }
  assert(intListIsEmpty(List));
  assert(intListOffEnd(List));
}

void intListMoveFirst(IntListHndl List){
  assert(!intListIsEmpty(List));
  
  List->current = List->first;
}

void intListMoveLast(IntListHndl List){
  assert(!intListIsEmpty(List));
  
  List->current = List->last;
}

void intListMovePrev(IntListHndl List){
  assert(!intListOffEnd(List));
  
  List->current = List->current->prev;
}

void intListMoveNext(IntListHndl List){
  assert(!intListOffEnd(List));
  
  List->current = List->current->next;
}

void intListInsertAtFront(IntListHndl List, int data){
  assert (List != NULL);
  
  IntNodePtr tmp = newIntNode(data);
  if (intListIsEmpty(List)) {
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

void intListInsertAtBack(IntListHndl List, int data){
  assert (List != NULL);
  
  IntNodePtr tmp = newIntNode(data);
  if (intListIsEmpty(List)) {
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

void intListInsertBeforeCurrent(IntListHndl List, int data){
  assert(!intListOffEnd(List));
  assert(List != NULL);
   
  if ((List->current) == (List->first)) {
    intListInsertAtFront(List, data);
  } else {
    IntNodePtr tmp = newIntNode(data);
    tmp->next=List->current;
	tmp->prev=List->current->prev;
	List->current->prev=tmp;
	tmp->prev->next=tmp;
	List->Length++;
  }

}

void intListDeleteFirst(IntListHndl List){
  assert (List != NULL);
  assert (!intListIsEmpty(List));
  
  if (List->Length == 1) {
    assert(List->first != NULL);
	freeIntNode(&List->first);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
  } else {
    if((List->first) == (List->current)){
	  IntNodePtr tmp = List->first;
      IntNodePtr tmp2 = tmp->next;
      tmp->next = NULL;
      tmp2->prev = NULL;
      List->first = tmp2;
      freeIntNode(&tmp);
      tmp = NULL;
	  List->current = NULL;
	}else{
      IntNodePtr tmp = List->first;
      IntNodePtr tmp2 = tmp->next;
      tmp->next = NULL;
      tmp2->prev = NULL;
      List->first = tmp2;
      freeIntNode(&tmp);
      tmp = NULL;
	}
  }
  List->Length--;
}

void intListDeleteLast(IntListHndl List){
  assert (List != NULL);
  assert (!intListIsEmpty(List));
  
  if (List->Length == 1) {
	freeIntNode(&List->last);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
  } else {
    if((List->last) == (List->current)){
      IntNodePtr tmp = List->last;
      IntNodePtr tmp2 = tmp->prev;
      tmp->prev = NULL;
      tmp2->next = NULL;
      List->last = tmp2;
      freeIntNode(&tmp);
      tmp = NULL;
	  List->current = NULL;
	}else{
	  IntNodePtr tmp = List->last;
      IntNodePtr tmp2 = tmp->prev;
      tmp->prev = NULL;
      tmp2->next = NULL;
      List->last = tmp2;
      freeIntNode(&tmp);
      tmp = NULL;
	}
  }
  List->Length--;
}

void intListDeleteCurrent(IntListHndl List){
  assert (List != NULL);
  assert (!intListIsEmpty(List));
  assert (!intListOffEnd(List));
  
  if (List->Length == 1) {
    freeIntNode(&List->first);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
	List->Length--;
  } else {
    if (intListAtFirst(List)) {
      intListDeleteFirst(List);
      List->current = NULL;
    } else if (intListAtLast(List)) {
      intListDeleteLast(List);
      List->current = NULL;
    } else {
      List->current->prev->next = List->current->next;
      List->current->next->prev = List->current->prev;
      freeIntNode(&List->current);
      List->current = NULL;
	  List->Length--;
    }
  }  

}

/*** Other operations ***/

void printIntList(FILE* out, IntListHndl List){
  assert (List != NULL);

  IntNodePtr tmp = List->first;
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