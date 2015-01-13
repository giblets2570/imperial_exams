braille: braille.o main.o
	g++ -Wall -g braille.o main.o -o braille

braille.o: braille.cpp braille.h
	g++ -Wall -g -c braille.cpp

main.o: main.cpp braille.h
	g++ -Wall -g -c main.cpp

clean:
	rm -f *.o braille