#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ctime>
#include "Algorithm.h"

using namespace std;

Sequence* query;     //query protein sequence
Database* db;     //choiced database
unsigned char* buffer;     //haeder file buffer
Blosum* blosum;     //score matrix
string matrixName = "BLOSUM62";  //name of the score matrix
int gapOpenPenalty;     //gap open penalty
int gapExtensionPenalty;     //gap extension penalty
time_t tbeg, tend;       //time measurement variables
double texec = 0;	//execution time

int main(int argc, char *argv[]) 
{
	tbeg = time(NULL); //measures time

	if((argc < 5) || (argc > 8))     //checking parameters
	{
		cout << "Erreur, veuillez vérifier les paramètres." << endl;
		return EXIT_FAILURE;
	}
	else
	{			
		query = new Sequence(argv[1]);     //init query 
			
		db = new Database(argv[2], argv[3]);     //init database
	
		ifstream file(argv[4], ios::in);     //init header file buffer
		if(file)
		{
			file.seekg(0, file.end);
			int length = file.tellg();
			file.seekg(0, file.beg);
			buffer = new unsigned char[length];
			file.read((char*)buffer, length);
		}
		if(argc > 5)                              //init score matrix
		{
			blosum = new Blosum(argv[5]);
			string matrixName = argv[5];
		}
		else
			blosum = new Blosum("BLOSUM62");
	
		if(argc > 6)                              //init gap open penalty
			gapOpenPenalty = atoi(argv[6]);
		else
			gapOpenPenalty = 11;
		if(argc > 7)                              //init gap extension penalty
			gapExtensionPenalty = atoi(argv[7]);
		else
			gapExtensionPenalty = 1;
		cout << "Searching" << endl;
		Algorithm* algo = new Algorithm(db, query, blosum, gapOpenPenalty, gapExtensionPenalty); //load search algorithm
		cout << "Done" << endl;
		
		tend = time(NULL);             //measures time
		texec = difftime(tend, tbeg);

		ofstream result("result.txt", ios::out | ios::trunc);   //print results
		if(result)
		{
			result << "Database title:  " << db->getTitle() << "\n";
			result << "Database size:  " << db->getResiduesSize() << " residues in " << db->getSequenceSize() << " sequences\n";
			result << "Longest db seq:  " << db->getLongestSeq() << " residues\n";
			result << "Query file name:  " << argv[1] << "\n";
			result << "Query length:  " << query->getLength() << " residues\n";
			result << "Query description" << query->getDescription() << "\n";
			result << "Score matrix:  " << matrixName << "\n";
			result << "Gap penalty:  " << gapOpenPenalty << "+" << gapExtensionPenalty << "k\n";
			result << "Execution time:  " << texec << "s\n";
			result << "----------------------------------------------------------------\n";
			for(int i = 0; i<100; i++)
			{
				Sequence* new_seq = new Sequence(buffer, db, algo->getSeqId()[i]);
				result << "gnl|" << new_seq->getIdInfo() << "|" << new_seq->getId() << " " << new_seq->getDescription() << "   SCORE : " << algo->getScore()[i] << "\n";
			}
		}	
		return EXIT_SUCCESS; 
	}
}
