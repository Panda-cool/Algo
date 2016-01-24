All: Algorithm.o Sequence.o Database.o Blosum.o main.cpp
	g++ Algorithm.o Sequence.o Database.o Blosum.o main.cpp -o main
Algorithm.o: Sequence.o Blosum.o Database.o Algorithm.cpp
	g++ Sequence.o Blosum.o Database.o -c Algorithm.cpp
Sequence.o: Database.o Sequence.cpp
	g++ Database.o -c Sequence.cpp
Database.o: Database.cpp
	g++ -c Database.cpp
Blosum.o: Blosum.cpp
	g++ -c Blosum.cpp
clean:
	rm *.o
