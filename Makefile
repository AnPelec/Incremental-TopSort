# Makefile adjusted from https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html

# the compiler: gcc for C program, define as g++ for C++
CC  = g++

# compiler flags:
#   -g adds debugging information
#   -Wall turns on most compiler warnings
#   -std=c++11 specifies c++11
CFLAGS = -g -Wall -std=c++11

# naive - O(mn) complexity algorithm
naive: naiveAlgorithm.cpp test.cpp
	$(CC) $(CFLAGS) -c naiveAlgorithm.cpp
	$(CC) $(CFLAGS) -c test.cpp
	$(CC) $(CFLAGS) -o testNaive test.o naiveAlgorithm.o

# ideal - O(n^2 log n) complexity algorithm
ideal: idealAlgorithm.cpp test.cpp
	$(CC) $(CFLAGS) -c idealAlgorithm.cpp
	$(CC) $(CFLAGS) -c test.cpp
	$(CC) $(CFLAGS) -c bst.cpp
	$(CC) $(CFLAGS) -o testIdeal test.o idealAlgorithm.o bst.o

# compile bst unit
bst: bst.cpp testBST.cpp
	$(CC) $(CFLAGS) -c bst.cpp
	$(CC) $(CFLAGS) -c testBST.cpp
	$(CC) $(CFLAGS) -o testBST bst.o testBST.cpp

clean:
	rm -f  *.o