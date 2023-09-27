GXX = g++
FLAG= -std=c++17 -Wall -pedantic -g

all: lab2

lab2: lab2.cpp
	$(GXX) $(FLAG) lab2.cpp -o lab

test:
	./lab2

valgrind:
	valgrind --leak-check=full --track-origins=yes -s ./lab

clear:
	rm -r *.o

del_report:
	rm -r report.log*