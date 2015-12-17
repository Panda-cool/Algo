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
			
			const char* headerName = "/home/student/Documents/algo/uniprot_sprot.fasta.phr";

			query = new Sequence(argv[1]); 
			cout << query->getDescription() << endl;
			cout << query->getChain() << endl;

			db = new Database(argv[2], argv[3]);
			cout << db->getTitle() << endl;
			cout << db->getResiduesSize() << endl;
			cout << db->getHeaderOffsets()[2] << endl;
			cout << db->getSequences()[6] << endl;
			
			ifstream file(argv[4], ios::in);
			if(file)
			{
				file.seekg(0, file.end);
				int length = file.tellg();
				file.seekg(0, file.beg);
				buffer = new unsigned char[length];
				file.read((char*)buffer, length);

				Sequence *seq = new Sequence(buffer, db, 2);
				cout << seq->getDescription() << endl;
				cout << seq->getId() << endl;
				cout << seq->getIdInfo() << endl;
			}
			if(argc > 5)
				blosum = new Blosum(argv[5]);
			else
				blosum = new Blosum("BLOSUM62");

			cout << blosum->getResidues() << endl;
			cout << blosum->Matrix[0][0] << endl;
			for(int j=0;j<24;j++)
			{
				for(int i=0;i<24;i++)
					cout << blosum->Matrix[i][j] << " ";
				cout << endl; 
			}
			
		
			if(argc > 6)
				gapOpenPenalty = atoi(argv[6]);
			else
				gapOpenPenalty = 11;
			cout << gapOpenPenalty << endl;
			if(argc > 7)
				gapExtensionPenalty = atoi(argv[7]);
			else
				gapExtensionPenalty = 1;
			cout << gapExtensionPenalty << endl;

		

		//TODO: algorithme
	}
	return EXIT_SUCCESS; 
}
