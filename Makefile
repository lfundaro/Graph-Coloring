all: main

mas: main

main: main.o dsatur.o implicit_enum.o backwards.o interchange.o twoOnN.o build_graph.o utilities.o Forward.o
	gcc main.o dsatur.o build_graph.o backwards.o implicit_enum.o twoOnN.o interchange.o utilities.o Forward.o -o main

estrella: main.o dsatur.o implicit_enum.o backwards.o interchange.o twoOnN.o build_graph.o utilities.o Forward_star.o
	gcc main.o dsatur.o build_graph.o backwards.o implicit_enum.o twoOnN.o interchange.o utilities.o Forward_star.o -o main

main.o: main.c
	gcc -c main.c main.h 

implicit_enum.o: implicit_enum.c
	gcc -c implicit_enum.c implicit_enum.h

backwards.o: backwards.c
	gcc -c backwards.c backwards.h

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

Forward.o: Forward.c
	gcc -c Forward.c Forward.h

Forwad_star.o: Forward_star.c
	gcc -c Forward_star.c Forward.h

clean:
	rm -rf *.o *.out semantic.cache *.gch *~  main