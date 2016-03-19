/* By Patrick Russell  and  Sam Reha
 *      pcrussel@ucsc.edu || sreha@ucsc.edu
 *
 * NAME: librarySort.c
 *
 * PURPOSE: Read in 2 files, then search for specified books
 *
 * USAGE: librarySort FILENAME1 FILENAME2
 *	             Where FILENAME1 contains:
 *                  -number of data lines
 *                  -size of hash table
 *                  -library number followed by book title
 *
 *               Where FILENAME2 contains:
 *                  -book requests (1 per line)
 *
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "hashDict.h"

int main(int argc, char **argv) {
    /* Determine if the correct filenames were used*/
    if(argc < 3 || argc > 3){
        printf("librarySort usage: librarySort FILENAME1 FILENAME2\n");
        printf("FILENAME1 contains:\n *# of data lines in file\n");
        printf(" *size to make hash table\n");
        printf(" *a library number followed by the book title\n");
        printf("FILENAME2 contains: Only the titles of books\n");
        return 0;
    }
    /*open the file*/
    FILE *input;
    input = fopen(argv[1], "r");
    int index = 0;
    int size = 0;
    int dataLines = 0;
    int tmp = 0;
    int libraryNum = 0;
    int newLine = 0;
    char *bookName;
    char charTemp[124];
   
    /*get the number of data lines*/
    if(fscanf(input, "%d", &tmp) != NULL){
        dataLines = tmp;
    }else{
        printf("ERROR: first line of file wasn't a number\n");
        return 0;
    }
   
    /*get the size of the array*/
    if(fscanf(input, "%d", &tmp) != NULL){
        size = tmp;
    }else{
        printf("ERROR: second line wasn't a number\n");
        return 0;
    }

    hashDictHndl table = newHashDict(dataLines);   

    /* Loop through the list, scanning the names and numbers.
     * 
     * Insert each pair of library numbers and book names
     * into the hash table
     */
    while(fscanf(input, "%d", &tmp) != EOF){
        newLine = 0;
        libraryNum = tmp;
      
        /*ignore the comma*/
        if (fscanf(input, "%s", &charTemp) != NULL){
        /*do nothing*/ 
        } else {
            printf("ERROR: there wasn't a comma\n");
            return 0;
        }
        /*printf("libraryNum = %d\n", libraryNum);*/
      
        /*scan in book names one char at a time 
         *until a newLine character is printed
         */
        while (newLine != 1) {
            /*get the first character*/
            int c = getc(input), idx = 0;
        
            /*ignore commas and spaces*/
            while (c == ' ' || c == ',') {
                c = getc(input);
            }
            if (c == EOF) break;
        
            /*set the character to the list*/
            charTemp[idx++] = c;
        
            /*get the rest of the word*/
            while (c != ' ' || idx <= 123) { 
                c = getc(input);
                if (c == EOF) {
                    charTemp[idx] = '\0';
                    newLine = 1;
                    break;
                } else if (c == '\n') {
                    /*if the word is the last word, break whole loop*/
                    charTemp[idx] = '\0';
                    newLine = 1;
                    break;
                } else charTemp[idx++] = c;
            }   
            charTemp[idx] = '\0';
        
            /*set the book name to the list of chars*/
            bookName = charTemp;

            hashDictInsert(table, charTemp, libraryNum);
            assert (hashDictLookUp(table, charTemp));
        }
    }
   /*printHashDict(stdout, table);*/
   fclose(input);

   input = fopen(argv[2], "r");

   if(fscanf(input, "%d", &tmp) != 0){
   /*do nothing */
   }

   int c = getc(input);

   while(c != EOF){
      /*c = getc(input);*/
      newLine = 0;
      if(c == '\n') c = getc(input);
      /*scan in book names one char at a time 
       *until a newLine character is printed
       */
      while (newLine != 1) {
         /*get the first character*/
         /*c = getc(input);*/
         int idx = 0;
         if (c == EOF) break;
        
         /*set the character to the list*/
         charTemp[idx++] = c;
        
         /*get the rest of the word*/
         while (c != ' ' || idx <= 123) {
            c = getc(input);
            if (c == EOF) {
               charTemp[idx] = '\0';
               newLine = 1;
               break;
            } else if (c == '\n') {
      /*if the word is the last word, break whole loop*/
               charTemp[idx] = '\0';
               newLine = 1;
               break;
            } else charTemp[idx++] = c;
         }
	 charTemp[idx] = '\0';
         
         /*set the book name to the list of chars*/
         bookName = charTemp;
         
	 /*printf("%s: ", bookName);*/
         if (hashDictLookUp(table, bookName)){ 
            printHashDictKeyData(stdout, table, bookName);
         }else {
            printf("%s: Not in hash table\n\n", bookName);
         } 
      }
   }   
   
   fclose(input);
   freeHashDict(&table);
   return 0;
}
