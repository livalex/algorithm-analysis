CC = g++
CFLAGS = -Wall -Wextra -O2
LDLIBS = -lm

build: algo.o

bellman_ford: algo_bellman_ford.cpp tester.cpp
	g++ algo_bellman_ford.cpp tester.cpp -o bellman_ford
	for number in 0 ; do \
		./bellman_ford test$$number test$$number ; \
	done 




algo.o: algo.cpp
	g++ algo.cpp -c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o
