/* By Patrick Russell   and Sam Reha
 *    pcrussel@ucsc.edu ||  sreha@ucsc.edu
 */

# include "IntList.h"
# include "myinclude.h"

typedef struct hashDictObj* hashDictHndl;

/* Note: All functions bear the implicit precondition that the required Hash Dictionary is a valid,
   non-null hashDictHndl. */

/*** CONSTRUCTORS AND DESTRUCTORS ***/
/* newHashDict()
   Constructor for the hashDict type, returns a properly initialized, empty hashDictHndl
   pre:
   post: */
hashDictHndl newHashDict(int tableSize);

/* freeHashDict();
   destructor for the hashDict type
   pre:
   post: pD == NULL, all memory has been freed */
void freeHashDict(hashDictHndl* pD);

/*** ACCESS FUNCTIONS ***/
/* hashDictIsEmpty()
   returns 1 (true) if D is empty, 0 (false) otherwise
   pre:
   post: */
int hashDictIsEmpty(hashDictHndl D);

/* hashDictSize()
   returns the number of (key, value) pairs in D
   pre:
   post: */
int hashDictSize(hashDictHndl D);

/* hashDictLookUp()
   returns TRUE if K is in D, or returns FALSE if no such value k exists.
   pre:
   post: */
Boolean hashDictLookUp(hashDictHndl D, char* k);

/*** MANIPULATION FUNCTIONS ***/
/* hashDictInsert()
   inserts new (key,value) pair into D. If k is already within D, v is appended to k's list.
   pre: hashDictLookUp(D, k) == FALSE
   post: D->length++, D now contains k and k contains v */
void hashDictInsert(hashDictHndl D, char* k, int v);

/* hashDictDelete()
   deletes pair with the key k
   pre: hashDictLookUp(D, k) == TRUE 
   post: D->length--, D no longer contains k */
void hashDictDelete(hashDictHndl D, char* k);

/* hashDictMakeEmpty()
   re-sets D to the empty state.
   pre: 
   post: D is completely empty */
void hashDictMakeEmpty(hashDictHndl D);

/*** OTHER FUNCTIONS ***/
/* printHashDict()
   prints a text representation of D to the file pointed to by out
   pre:
   post */
void printHashDict(FILE* out, hashDictHndl D);

/* printHashDictKeyData()
   prints a text representation of a key's data to the file pointed to by out
   pre: hashDictLookUp(D, key) == TRUE
   post: */
void printHashDictKeyData(FILE* out, hashDictHndl D, char* key);