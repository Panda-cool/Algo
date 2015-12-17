all: Blosum.o Database.o Sequence.o main.cpp
	g++ Blosum.o Database.o Sequence.o main.cpp -o main
Sequence.o: Database.o Sequence.cpp
	g++ Database.o -c Sequence.cpp
Database.o: Database.cpp
	g++ -c Database.cpp
Blosum.o: Blosum.cpp
	g++ -c Blosum.cpp
clean:
	rm *.o
