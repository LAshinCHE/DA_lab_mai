GXX = g++
FLAG= -std=c++17 -Wall -pedantic -Werror -g

all: lab1 test

lab1: lab1.cpp KeyAndValue.cpp sorting.cpp
	$(GXX) $(FLAG) lab1.cpp KeyAndValue.cpp sorting.cpp -o lab

lab: lab
	./lab < test

test: test.cpp KeyAndValue.cpp sorting.cpp
	$(GXX) $(FLAG) test.cpp KeyAndValue.cpp sorting.cpp -o t

t: t test
	./t < test

clear:
	rm -r *.o
