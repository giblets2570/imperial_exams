sonnet: sonnet.o main.o
	g++ -Wall -g sonnet.o main.o -o sonnet

sonnet.o: sonnet.cpp sonnet.h
	g++ -Wall -g -c sonnet.cpp

main.o: main.cpp sonnet.h
	g++ -Wall -g -c main.cpp

clean:
	rm -f *.o sonnet