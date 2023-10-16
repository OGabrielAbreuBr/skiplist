all: lista.o main.o
	gcc lista.o main.o -o lista -std=c99 -Wall

lista.o:
	gcc -c skiplist.c -o lista.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o lista

run:
	./lista
