# makefile for p7, program for Six Degrees of Bacon

# defining target dependencies and files
p7: main.o Bacon.o
	g++ -o p7 main.o Bacon.o -Wall

# defining how each object file is to be built
main.o: main.cpp Bacon.h
	g++ -c main.cpp -Wall

Bacon.o: Bacon.cpp Bacon.h
	g++ -c Bacon.cpp -Wall

# clean up
clean:
	rm -f p7 *.o *~
