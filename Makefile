all: dog

dog: main.o fun.o 
	gcc main.o fun.o

main.o: main.c
	gcc -c main.c

fun.o: fun.c
	gcc -c fun.c

clean:
	rm *.o