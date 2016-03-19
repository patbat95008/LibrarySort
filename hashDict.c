/*-----------------------------------------------------------------------------
// By Samuel Reha    and Patrick Russell
//      sreha@ucsc.edu  ||  pcrussel@ucsc.edu
// 
// Date: 5/19/13
//
// NAME: hashDict.c
//
// PURPOSE: Provides a definition for Dictionay.h as described in the PA 5 spec. Creates
//                   a simple hashDict data type.
//
// Notes: Implements a hashing function described by P. Tantalo during CMPS 12B: Summer '14
//
//----------------------------------------------------------------------------- */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "hashDict.h"
# include "hashDictList.h"
# include "IntList.h"

/* hashDict functions --------------------------------------
// hashDictObj */
typedef struct hashDictObj {
    int numItems;
    int sizeOfTable;
    hashDictHndl* table;
} hashDictObj;

/* hashDict
// rotate_left()
// rotate the bits in an unsigned int */
unsigned int rotate_left(unsigned int value, int shift) {
    int sizeInBits = 8*sizeof(unsigned int);
    shift = shift & (sizeInBits - 1);
    if ( shift == 0 )
        return value;
    return (value << shift) | (value >> (sizeInBits - shift));
}

/* pre_hash()
// turn a string into an unsigned int */
unsigned int pre_hash(char* input) {
    unsigned int result = 0xBAE86554;
    while (*input) {
        result ^= *input++;
        result = rotate_left(result, 5);
    }
    return result;
}

/* hash()
// turns a string into an int in the range 0 to tableSize-1 */
int hash(hashDictHndl D, char* key){
    return pre_hash(key)%D->sizeOfTable;
}

/*** public functions ***/
hashDictHndl newHashDict(int tableSize) {
    assert (tableSize > 0);

    hashDictHndl D = malloc(sizeof(hashDictObj));
    assert(D != NULL);
    
    D->table = calloc(tableSize, sizeof(HashDictListHndl));
    D->numItems = 0;
    D->sizeOfTable = tableSize;
    return D;
}

void freeHashDict(hashDictHndl* pD) {
    assert (pD != NULL);
    assert (*pD != NULL);

    if (!hashDictIsEmpty(*pD)) {
        hashDictMakeEmpty(*pD);
    }
    hashDictHndl D = *pD;
    free(D->table);
    free(*pD);
    *pD = NULL;
}

int hashDictIsEmpty(hashDictHndl D) {
    assert (D != NULL);
    
    return (D->numItems == 0);
}

int hashDictSize(hashDictHndl D) {
    assert (D != NULL);
    return (D->numItems);
}

Boolean hashDictLookUp(hashDictHndl D, char* k) {
    assert (D != NULL);
    int i;

    i = hash(D, k);
    if (D->table[i] == NULL) {
        return 0;
    } else {
        return (hashDictListLookUp(D->table[i], k));
    }
}

void hashDictInsert(hashDictHndl D, char* k, int v) {
    assert (D != NULL);
    int i;

    i = hash(D, k);
    if (D->table[i] == NULL) {
        D->table[i] = newHashDictList();
    }
    if (hashDictListLookUp(D->table[i], k)) {
        hashDictListAppendLibrary(D->table[i], k, v);
    } else {
        hashDictListInsertAtBack(D->table[i], k);
        hashDictListAppendLibrary(D->table[i], k, v);
    }
    D->numItems++;
}

void hashDictDelete(hashDictHndl D, char* k) {
    assert (D != NULL);
    assert (D->numItems > 0);
    assert (hashDictLookUp(D, k));
    int i;

    i = hash(D, k);
    hashDictListDeleteKey(D->table[i], k);
    D->numItems--;
}

void hashDictMakeEmpty(hashDictHndl D) {
    assert (D != NULL);
    int i;
    
    if (D->numItems > 0) {
        for (i = 0; i < D->sizeOfTable; i++) {
            if (D->table[i] != NULL) {
                freeHashDictList(&D->table[i]);
            }
        }
    }
    D->numItems = 0;
}

void printHashDict(FILE* out, hashDictHndl D) {
    assert (D != NULL);
    int i;
    
    for (i = 0; i < D->sizeOfTable; i++) {
        if (D->table[i] != NULL) {
            printHashDictList(stdout, D->table[i]);
        }
    }
}

void printHashDictKeyData(FILE* out, hashDictHndl D, char* key) {
    assert (D != NULL);
    assert (hashDictLookUp(D, key));
    int i; 
    i = hash(D, key);
    printHashDictList(stdout, D->table[i]);
    
}
