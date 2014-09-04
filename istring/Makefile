a.out : main.o istring.o istring.h
	gcc -std=c99 -Wall -g main.o istring.o -o a.out

main.o : main.c istring.h
	gcc -std=c99 -Wall -g -c main.c 

istring.o : istring.c istring.h
	gcc -std=c99 -Wall -g -c istring.c
