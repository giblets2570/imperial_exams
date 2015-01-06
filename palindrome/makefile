words: words.o main.o
	g++ -g words.o main.o -o words

main.o: main.cpp words.h
	g++ -Wall -g -c main.cpp

words.o: words.cpp words.h
	g++ -Wall -g -c words.cpp

clean:
	rm *.o words
