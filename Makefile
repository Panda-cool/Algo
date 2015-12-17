all: Database.o Sequence.o main.cpp
	g++ Database.o Sequence.o main.cpp -o main
Sequence.o: Database.o Sequence.cpp
	g++ Database.o -c Sequence.cpp
Database.o: Database.cpp
	g++ -c Database.cpp
clean:
	rm *.o
