all: lista.o item.o main.o
	gcc lista.o main.o item.o -o skiplist -std=c99 -Wall

lista.o:
	gcc -c lista.c -o lista.o
	 
main.o:
	gcc -c main.c -o main.o

item.o:
	gcc -c item.c -o item.o
	 
clean:
	rm *.o skiplist

run:
	./skiplist
