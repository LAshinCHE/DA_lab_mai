GXX = g++
FLAG= -std=c++17 -Wall -pedantic -g

all: lab2

lab2: lab2.cpp
	$(GXX) $(FLAG) -pg lab2.cpp -o lab


test:
	./lab < test

valgrind:
	valgrind --leak-check=full --track-origins=yes --log-file="logf.txt" -s ./lab

clear:
	rm -r *.o

del_report:
	rm -r report.log*