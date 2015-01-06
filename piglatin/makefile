piglatin: piglatin.o main.o
	g++ -Wall -g piglatin.o main.o -o piglatin

main.o: main.cpp piglatin.h
	g++ -Wall -g -c main.cpp

piglatin.o: piglatin.cpp piglatin.h
	g++ -Wall -g -c piglatin.cpp

clean:
	rm -f *.o piglatin
