ccp: 1.o
	g++ -std=c++17 1.cpp -o test -lstdc++fs

1.o: 1.cpp
	g++ -g -O0 -c 1.cpp

clean:
	rm kk *.o

indent:
	indent -kr -nut -ts4 1.cpp

