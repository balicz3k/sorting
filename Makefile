CC=g++
CFLAGS=-c -Wall
LFLAGS=-Wall

all: sort

sort: main.o sort.o
	$(CC) $(LFLAGS) main.o sort.o -o sort

main.o: main.cpp sort.hpp
	$(CC) $(CFLAGS) main.cpp

sort.o: sort.cpp sort.hpp
	$(CC) $(CFLAGS) sort.cpp

clean:
	rm -rf *.o sort