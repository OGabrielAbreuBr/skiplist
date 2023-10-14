all: item.o skiplist.o main.o
	gcc item.o skiplist.o main.o -o main -std=c99 -Wall

item.o:
	gcc -c item.c -o item.o

skiplist.o:
	gcc -c skiplist.c -o skiplist.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o skiplist

run:
	./main
