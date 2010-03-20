all: main

main: main.o degree.o dsatur.o interchange.o utilities.o 
	gcc main.o degree.o dsatur.o interchange.o utilities.o -o main

degree.o: degree.c
	gcc -c degree.c

main.o: main.c
	gcc -c main.c main.h 

dsatur.o: dsatur.c
	gcc -c dsatur.c

interchange.o: interchange.c
	gcc -c interchange.c

utilities.o: utilities.c
	gcc -c utilities.c

clean:
	rm -rf *.o *.out semantic.cache *.gch *~  main

