all: main

mas: main

main: main.o dsatur.o implicit_enum.o backwards.o interchange.o twoOnN.o build_graph.o utilities.o Forward.o
	gcc main.o dsatur.o build_graph.o backwards.o implicit_enum.o twoOnN.o interchange.o utilities.o Forward.o -o main

estrella: main.o dsatur.o implicit_enum.o backwards.o interchange.o twoOnN.o build_graph.o utilities.o Forward_prime.o
	gcc main.o dsatur.o build_graph.o backwards.o implicit_enum.o twoOnN.o interchange.o utilities.o Forward_prime.o -o main

main.o: main.c
	gcc -c -g main.c main.h 

implicit_enum.o: implicit_enum.c
	gcc -c -g implicit_enum.c implicit_enum.h

backwards.o: backwards.c
	gcc -c -g backwards.c backwards.h

dsatur.o: dsatur.c
	gcc -c -g dsatur.c dsatur.h

interchange.o: interchange.c
	gcc -c -g interchange.c interchange.h

build_graph.o: build_graph.c
	gcc -c -g build_graph.c build_graph.h

twoOnN.o: twoOnN.c
	gcc -c -g twoOnN.c twoOnN.h

utilities.o: utilities.c
	gcc -c -g utilities.c utilities.h

Forward.o: Forward.c
	gcc -c -g Forward.c Forward.h

Forwad_star.o: Forward_prime.c
	gcc -c -g Forward_prime.c Forward.h

clean:
	rm -rf *.o *.out semantic.cache *.gch *~  main