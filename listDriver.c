/*
 * By: Patrick Russell  and  Sam Reha
 *       pcrussel@ucsc.edu || sreha@ucsc.edu
 *
 * NAME: listDriver.c
 *
 * PURPOSE: Test the ADT functions of program 4
 *
 */

# include <assert.h>

# include "myinclude.h"
# include "IntList.h"
# include "hashDictList.h"

int main (){
  /***Exercise IntList constructor***/
  IntListHndl IntList;
  IntList = NULL;
  IntList = newIntList ();

  if(IntList){
    printf("IntList Created\n");
  }else{
    printf("IntList Not Created\n");
  }
  
  printf("Expected value 1:\n");
  printf("intListIsEmpty %d\n",intListIsEmpty(IntList)); /*should print 1*/
  
  /***Populate with test data***/
  long i;
  for(i=0; i<=4; i++){
    intListInsertAtFront(IntList,i);
  }
  
  printIntList(stdout, IntList);
  
  printf("Expected value 0:\n");
  printf("intListIsEmpty %d\n",intListIsEmpty(IntList)); /*should print 0*/

  long j;
  for(j=5; j<=9; j++){
    intListInsertAtBack(IntList,j);
  } 
  printIntList(stdout, IntList);
  
  /***Exercise all access functions***/
  printf("Expected value 0:\n");
  printf("offEnd %d\n",intListOffEnd(IntList));/*should print 0*/
  
  printf("Expected value 0:\n");
  printf("atFirst %d\n",intListAtFirst(IntList));/*should print 0*/
  
  printf("Expected value 0:\n");
  printf("atLast %d\n",intListAtLast(IntList));/*should print 0*/
  
  printf("Expected value 4:\n");
  printf("getFirst %li\n", intListGetFirst(IntList));/*should print 4*/
  
  printf("Expected value 9:\n");
  printf("getLast %li\n", intListGetLast(IntList));/*should print 9*/
  
  printf("Expected value 0:\n");
  printf("getCurrent %li\n", intListGetCurrent(IntList));/*should print 0*/
  
  /***Exercise all removal manipulation functions***/
  intListDeleteLast(IntList);
  printIntList(stdout, IntList);
  printf("Expected value 8:\n");
  printf("getLast %li\n", intListGetLast(IntList));/*should print 8*/
  
  intListDeleteFirst(IntList);
  printIntList(stdout, IntList);
  printf("Expected value 3:\n");
  printf("getFirst %li\n", intListGetFirst(IntList));/*should print 3*/
  
  intListDeleteCurrent(IntList);
  printIntList(stdout, IntList);
  
  intListMoveLast(IntList);
  printIntList(stdout, IntList);
  intListMovePrev(IntList);
  printIntList(stdout, IntList);
  intListMoveNext(IntList);
  printIntList(stdout, IntList);

  intListMakeEmpty(IntList);
  intListInsertAtFront(IntList, 40);
  intListMoveFirst(IntList);
  intListDeleteCurrent(IntList);
  
  intListInsertAtFront(IntList, 41);
  intListInsertAtBack(IntList, 42);
  intListMoveFirst(IntList);
  intListInsertBeforeCurrent(IntList, 43);
  printIntList(stdout, IntList);
  
  
  intListDeleteCurrent(IntList);
  printIntList(stdout, IntList);
  
  intListMakeEmpty(IntList);
  printf("Expected value 1:\n");
  printf("offEnd %d\n",intListOffEnd(IntList));/*should print 1*/
  
  /***Exercise IntList destructor***/
  freeIntList(&IntList);
  
  /*** Test HashDictList ***/
  printf("BEGIN HASHDICTLIST TEST\n\n");
  
  HashDictListHndl aList = newHashDictList();
  assert (aList != NULL);
  
  /*** Populate With Data ***/
  hashDictListInsertAtFront(aList, "fart");
  hashDictListInsertAtFront(aList, "butt");
  hashDictListInsertAtFront(aList, "hat");
  hashDictListInsertAtFront(aList, "Joe");
  hashDictListInsertAtFront(aList, "Orange");
  
  hashDictListInsertAtBack(aList, "blarp");
  hashDictListInsertAtBack(aList, "Bleeble");
  hashDictListInsertAtBack(aList, "Mulan");
  hashDictListInsertAtBack(aList, "know");
  hashDictListInsertAtBack(aList, "neat");
  
  printHashDictListNode(stdout, aList, hashDictListGetFirst(aList));
  
  hashDictListAppendLibrary(aList, "fart", 1);
  printHashDictListNode(stdout, aList, "fart");
  
  hashDictListAppendLibrary(aList, "fart", 2);
  printHashDictListNode(stdout, aList, "fart");
  
  hashDictListAppendLibrary(aList, "butt", 45);
  
  printHashDictList(stdout, aList);
  
  /*** Exercise Delete Operations ***/
  hashDictListDeleteCurrent(aList);
  hashDictListDeleteLast(aList);
  
  /*** Exercise IntList destructor ***/
  freeHashDictList(&aList);
  
  return(0);
} 