tube: tube.o main.o
	g++ -Wall -g tube.o main.o -o tube

tube.o: tube.cpp tube.h
	g++ -Wall -g -c tube.cpp 

main.o: main.cpp tube.h
	g++ -Wall -g -c main.cpp

clean:
	rm -f *.o tube