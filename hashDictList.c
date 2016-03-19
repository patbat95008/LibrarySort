/*
 * By Samuel Reha  and Patrick Russell
 *    sreha@ucsc.edu || pcrussel@ucsc.edu
 * Created: 5/21/14
 * CMPS 101 Spring '14 Programming Assignment 4:
 *
 * NAME: hashDictList.c
 *
 * PURPOSE: This ADT implements the interface defined in hashDictList.h. 
 *                  This is a doubly-linked list of string / IntList pairs. Based on a 
 * 
 * list originally written by Samuel Reha and Nico Williams.
 */

# include "myinclude.h"
# include <assert.h>
# include <string.h>
# include "hashDictList.h"
# include "IntList.h"

typedef struct HashDictNodeStruct* HashDictListNodePtr;

typedef struct HashDictListStruct {
  int Length;
  HashDictListNodePtr first;
  HashDictListNodePtr last;
  HashDictListNodePtr current;
} HashDictListStruct;

typedef struct HashDictNodeStruct {
  char* name;
  IntListHndl list;
  struct HashDictNodeStruct* next;
  struct HashDictNodeStruct* prev;
} HashDictNodeStruct;


/*** Constructors-Destructors ***/

HashDictListHndl newHashDictList (){
  HashDictListHndl tempList = malloc ( sizeof(HashDictListStruct) );
  assert(tempList != NULL);
  
  tempList->Length = 0;
  tempList->current = NULL;
  tempList->first = NULL;
  tempList->last = NULL;
  
  return (tempList);
}  

void freeHashDictList (HashDictListHndl *List){
  assert ((*List) != NULL && List != NULL); 
  while (! hashDictListIsEmpty((*List))) {
    hashDictListDeleteLast(*List); 
  }
  free (*List);
  *List = NULL;
}

HashDictListNodePtr newHashDictNode(char* data) {
	HashDictListNodePtr tempNode = malloc(sizeof(HashDictNodeStruct));
	assert(tempNode != NULL);
	
	tempNode->name = calloc (sizeof(char), 40);
    strcpy(tempNode->name, data);
    
    tempNode->list = newIntList();
	tempNode->next = NULL;
	tempNode->prev = NULL;
	return(tempNode);
}

void freeHashDictNode(HashDictListNodePtr *Node) {
	assert(*Node != NULL && Node != NULL);
    
    HashDictListNodePtr temp = *Node;
    freeIntList(&temp->list);
    free(temp->name);
    
	free(*Node);
	*Node = NULL;
	
}
  
/*** Access functions ***/

Boolean hashDictListIsEmpty(HashDictListHndl L){
   assert (L != NULL);

   return (L->Length == 0);
}

Boolean hashDictListOffEnd(HashDictListHndl L) {
  assert(L != NULL);
  
  return (L->current == NULL);
}

Boolean hashDictListAtFirst(HashDictListHndl L) {
  assert (L != NULL);
  
  return (L->current == L->first && !hashDictListOffEnd(L));
}

Boolean hashDictListAtLast(HashDictListHndl L) {
  assert (L != NULL);
  
  return (L->current == L->last && !hashDictListOffEnd(L));
}

Boolean hashDictListLookUp(HashDictListHndl L, char* someName) {
    assert(L != NULL);
    
    int foundIt = 0;
    HashDictListNodePtr temp = L->first;
    
    while (temp != NULL) {
        if (!strcmp(temp->name, someName)) {
            foundIt = 1;
            break;
        }
        temp = temp->next;
    }
    
    return (foundIt);
}

char* hashDictListGetFirst(HashDictListHndl List) {
  assert (List != NULL);
  assert (!hashDictListIsEmpty(List));
  
  return (List->first->name);
}

char* hashDictListGetLast(HashDictListHndl List) {
  assert (List != NULL);
  assert (!hashDictListIsEmpty(List));
  
  return (List->last->name);
}

char* hashDictListGetCurrent(HashDictListHndl List) {
  assert (List != NULL);
  assert (!hashDictListIsEmpty(List));
  assert (List->current != NULL);
  
  return (List->current->name);
}

/*** Manipulation Procedures ***/

void hashDictListAppendLibrary(HashDictListHndl L, char* someName, int someValue) {
    assert (L != NULL);
    assert (hashDictListLookUp(L, someName));
    
    HashDictListNodePtr temp = L->first;
    
    while (strcmp(temp->name, someName) && temp != NULL) {
        temp = temp->next;
    }
    assert (temp != NULL);
    
    intListInsertAtBack(temp->list, someValue);
}

void hashDictListMakeEmpty(HashDictListHndl L){
    assert (L != NULL);

    while(L->Length > 0){
        hashDictListDeleteFirst(L);
    }
    assert(hashDictListIsEmpty(L));
    assert(hashDictListOffEnd(L));
}

void hashDictListMoveFirst(HashDictListHndl L){
    assert (L != NULL);
    assert (!hashDictListIsEmpty(L));
  
    L->current = L->first;
}

void hashDictListMoveLast(HashDictListHndl L){
    assert (L != NULL);
    assert (!hashDictListIsEmpty(L));
  
    L->current = L->last;
}

void hashDictListMovePrev(HashDictListHndl L){
    assert (L != NULL);
    assert(!hashDictListOffEnd(L));
  
    L->current = L->current->prev;
}

void hashDictListMoveNext(HashDictListHndl L){
    assert (L != NULL);
    assert(!hashDictListOffEnd(L));
  
    L->current = L->current->next;
}

void hashDictListInsertAtFront(HashDictListHndl List, char* data){
    assert (List != NULL);
  
    HashDictListNodePtr tmp = newHashDictNode(data);
    if (hashDictListIsEmpty(List)) {
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

void hashDictListInsertAtBack(HashDictListHndl List, char* data){
  assert (List != NULL);
  
  HashDictListNodePtr tmp = newHashDictNode(data);
  if (hashDictListIsEmpty(List)) {
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

void hashDictListInsertBeforeCurrent(HashDictListHndl List, char* data){
  assert(!hashDictListOffEnd(List));
  assert(List != NULL);
   
  if ((List->current) == (List->first)) {
    hashDictListInsertAtFront(List, data);
  } else {
    HashDictListNodePtr tmp = newHashDictNode(data);
    tmp->next=List->current;
	tmp->prev=List->current->prev;
	List->current->prev=tmp;
	tmp->prev->next=tmp;
	List->Length++;
  }

}

void hashDictListDeleteFirst(HashDictListHndl List){
  assert (List != NULL);
  assert (!hashDictListIsEmpty(List));
  
  if (List->Length == 1) {
    assert(List->first != NULL);
	freeHashDictNode(&List->first);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
  } else {
    if((List->first) == (List->current)){
	  HashDictListNodePtr tmp = List->first;
      HashDictListNodePtr tmp2 = tmp->next;
      tmp->next = NULL;
      tmp2->prev = NULL;
      List->first = tmp2;
      freeHashDictNode(&tmp);
      tmp = NULL;
	  List->current = NULL;
	}else{
      HashDictListNodePtr tmp = List->first;
      HashDictListNodePtr tmp2 = tmp->next;
      tmp->next = NULL;
      tmp2->prev = NULL;
      List->first = tmp2;
      freeHashDictNode(&tmp);
      tmp = NULL;
	}
  }
  List->Length--;
}

void hashDictListDeleteLast(HashDictListHndl List){
  assert (List != NULL);
  assert (!hashDictListIsEmpty(List));
  
  if (List->Length == 1) {
	freeHashDictNode(&List->last);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
  } else {
    if((List->last) == (List->current)){
      HashDictListNodePtr tmp = List->last;
      HashDictListNodePtr tmp2 = tmp->prev;
      tmp->prev = NULL;
      tmp2->next = NULL;
      List->last = tmp2;
      freeHashDictNode(&tmp);
      tmp = NULL;
	  List->current = NULL;
	}else{
	  HashDictListNodePtr tmp = List->last;
      HashDictListNodePtr tmp2 = tmp->prev;
      tmp->prev = NULL;
      tmp2->next = NULL;
      List->last = tmp2;
      freeHashDictNode(&tmp);
      tmp = NULL;
	}
  }
  List->Length--;
}

void hashDictListDeleteCurrent(HashDictListHndl List){
  assert (List != NULL);
  assert (!hashDictListIsEmpty(List));
  assert (!hashDictListOffEnd(List));
  
  if (List->Length == 1) {
    freeHashDictNode(&List->first);
    List->current = NULL;
    List->first = NULL;
    List->last = NULL;
	List->Length--;
  } else {
    if (hashDictListAtFirst(List)) {
      hashDictListDeleteFirst(List);
      List->current = NULL;
    } else if (hashDictListAtLast(List)) {
      hashDictListDeleteLast(List);
      List->current = NULL;
    } else {
      List->current->prev->next = List->current->next;
      List->current->next->prev = List->current->prev;
      freeHashDictNode(&List->current);
      List->current = NULL;
	  List->Length--;
    }
  }  

}

void hashDictListDeleteKey(HashDictListHndl L, char* k) {
    L->current = L->first;
    
    while(L->current != NULL && L->current->name != k) {
        L->current = L->current->next;
    }
    hashDictListDeleteCurrent(L);
}

/*** Other operations ***/

void printHashDictList(FILE* out, HashDictListHndl List){
    assert (List != NULL);
    assert (!hashDictListIsEmpty(List));

    HashDictListNodePtr tmp = List->first;
    while (tmp != NULL){
        printf("%s: ", tmp->name);
        printIntList(stdout, tmp->list);
    
        tmp = tmp->next;
        printf("\n");
    }
}

void printHashDictListNode(FILE* out, HashDictListHndl List, char* nameOfNode) {
    assert (nameOfNode != NULL);
    assert (hashDictListLookUp(List, nameOfNode));
  
    HashDictListNodePtr Node = List->first;
  
    while ((Node->name != nameOfNode) && (Node != NULL)) {
        Node = Node->next;
    }
    assert(Node != NULL);

    printIntList(stdout, Node->list);
}