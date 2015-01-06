correct: correct.o main.o
	g++ -Wall -g correct.o main.o -o correct

correct.o: correct.cpp correct.h
	g++ -Wall -g -c correct.cpp

main.o: main.cpp correct.h
	g++ -Wall -g -c main.cpp

clean:
	rm -f *.o correct