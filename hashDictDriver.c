/*
 * Samuel Reha - sreha@ucsc.edu
 * Last Modified: 5/20/2014
 * CMPS 101 Spring '14 Programming Assignment 4:
 * A test-client for hashDict.h and hashDict.c, hashDictDriver is intended to verify the correctness of the 
 * hashDict ADT. Though hashDictDriver does not exercise every imaginable edge case, it was valuable in
 * determining memory errors and memory leaks.
 */
 
# include <assert.h>
# include "myinclude.h"
# include "hashDict.h"

int main(void) {
    hashDictHndl somehashDict = newHashDict(15);
    assert (somehashDict != NULL);
    printf("somehashDict instantiated correctly\n");
    
    printf("Begin insertion operations:\n");
    hashDictInsert(somehashDict, "fart", 111);
    hashDictInsert(somehashDict, "fart", 243);
    hashDictInsert(somehashDict, "fart", 123412);
    
    hashDictInsert(somehashDict, "awe", 243);
    hashDictInsert(somehashDict, "awe", 1243);
    hashDictInsert(somehashDict, "awe", 34576);
    
    hashDictInsert(somehashDict, "nico", 3456);
    hashDictInsert(somehashDict, "nico", 99);
    hashDictInsert(somehashDict, "nico", 1523);
    printf("Conclude insertion operations.\n");
    
    printHashDict(stdout, somehashDict);
    printHashDictKeyData(stdout, somehashDict, "fart");

    freeHashDict(&somehashDict);
}