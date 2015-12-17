#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Sequence.h"
#include "Blosum.h"

using namespace std;

Sequence* query;
Database* db;
unsigned char* buffer;
Blosum* blosum;
int gapOpenPenalty;
int gapExtensionPenalty;


int main(int argc, char *argv[]) 
{
	if((argc < 5) || (argc > 8))
	{
		cout << "Erreur, veuillez vérifier les paramètres." << endl;
		return EXIT_FAILURE;
	}
	else
	{			
		query = new Sequence(argv[1]); 
			
		db = new Database(argv[2], argv[3]);
	
		ifstream file(argv[4], ios::in);
		if(file)
		{
			file.seekg(0, file.end);
			int length = file.tellg();
			file.seekg(0, file.beg);
			buffer = new unsigned char[length];
			file.read((char*)buffer, length);
		}
		if(argc > 5)
			blosum = new Blosum(argv[5]);
		else
			blosum = new Blosum("BLOSUM62");
	
		if(argc > 6)
			gapOpenPenalty = atoi(argv[6]);
		else
			gapOpenPenalty = 11;
		if(argc > 7)
			gapExtensionPenalty = atoi(argv[7]);
		else
			gapExtensionPenalty = 1;

		

		//TODO: algorithme

		return EXIT_SUCCESS; 
	}
}
