all: main

main: main.o degree.o dsatur.o interchange.o twoOnN.o build_graph.o utilities.o 
	gcc main.o degree.o dsatur.o build_graph.o twoOnN.o interchange.o utilities.o -o main

degree.o: degree.c
	gcc -c degree.c degree.h

main.o: main.c
	gcc -c main.c main.h 

dsatur.o: dsatur.c
	gcc -c dsatur.c dsatur.h

interchange.o: interchange.c
	gcc -c interchange.c interchange.h

build_graph.o: build_graph.c
	gcc -c build_graph.c build_graph.h

twoOnN.o: twoOnN.c
	gcc -c twoOnN.c twoOnN.h

utilities.o: utilities.c
	gcc -c utilities.c utilities.h

clean:
	rm -rf *.o *.out semantic.cache *.gch *~  main

