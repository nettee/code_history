all : a.out
a.out : main.o sllist.o sllist.h defs.h
	gcc -std=c99 -Wall -o a.out main.o sllist.o

sllist.o : sllist.c sllist.h defs.h
	gcc -std=c99 -Wall -c sllist.c

main.o : main.c sllist.h defs.h
	gcc -std=c99 -Wall -c main.c

