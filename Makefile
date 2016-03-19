# By Patrick Russell   and Sam Reha
#    pcrussel@ucsc.edu     sreha@ucsc.edu
#
# Makefile for programming assignment 4
# compiles librarySort executable

GCC = gcc -ansi -Wall -Wextra -pedantic
# GCC = c99

all: librarySort hashDictDriver

librarySort : librarySort.o hashDict.o hashDictList.o
	${GCC} -o librarySort librarySort.o hashDict.o hashDictList.o IntList.o

hashDictDriver: hashDictDriver.o hashDict.o hashDictList.o IntList.o
	${GCC} -o hashDictDriver hashDictDriver.o hashDict.o hashDictList.o IntList.o
    
listDriver : listDriver.o IntList.o hashDictList.o
	${GCC} -o listDriver listDriver.o IntList.o hashDictList.o

librarySort.o : librarySort.c hashDict.h
	${GCC} -c librarySort.c

hashDict.o : hashDictList.h hashDict.h hashDict.c
	${GCC} -c hashDict.c

IntList.o : IntList.h IntList.c
	${GCC} -c IntList.c

hashDictList.o : IntList.h hashDictList.h hashDictList.c
	${GCC} -c hashDictList.c


clean :
	rm hashDictList.o intList.o librarySort.o StringList.o hashDict.o
