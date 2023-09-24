GXX = g++
FLAGS= -std=c++17 -Wall -Pedantic -g

all: lab2

lab2: lab2.cpp
	$(GXX) $(FLAG) lab2.cpp -o lab2

test:
	./lab2

valgrind: lab2
	valgrind --leak-check=full --track-origins=yes ./lab2

clear:
	rm -r *.o