#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Database.h"
//#include "Sequence.h"

using namespace std;

//TODO:Score matrix
int gapOpenPenalty;
int gapExtensionPenalty;
//Sequence query;


int main(int argc, char *argv[]) 
{
	/*if((argc < 3) || (argc > 6))
	{
		cout << "Erreur, veuillez vérifier les paramètres." << endl;
		return -1;
	}
	else
	{*/
		//query = Sequence(argv[1]); //juste l'idée générale, à modifier
			const char* indexName = "/home/student/Documents/algo/uniprot_sprot.fasta.pin";
			const char* seqName = "/home/student/Documents/algo/uniprot_sprot.fasta.psq";
			const char* headerName = "/home/student/Documents/algo/uniprot_sprot.fasta.phr";

			Database *db = new Database(indexName, seqName);
			cout << db->getTitle() << endl;
			cout << db->getResiduesSize() << endl;
			cout << db->getHeaderOffsets()[2] << endl;
			cout << db->getSequences()[6] << endl;
			
			ifstream file(headerName, ios::in);
			if(file)
			{
				file.seekg(0, file.end);
				int length = file.tellg();
				file.seekg(0, file.beg);
				unsigned char* buffer = new unsigned char[length];
				file.read((char*)buffer, length);

				Sequence *seq = new Sequence(buffer, db->getHeaderOffsets()[2]);
				cout << seq->getDescription() << endl;
				cout << seq->getId() << endl;
				cout << seq->getIdInfo() << endl;
			}
		//if(argv[3] != NULL)
			//matrix = argv[3];
		//else
			//matrix = blosum62;
		/*if(argv[4] != NULL)
			gapOpenPenalty = atoi(argv[4]);
		else
			gapOpenPenalty = 11;
		if(argv[5] != NULL)
			gapExtensionPenalty = atoi(argv[5]);
		else
			gapExtensionPenalty = 1;*/

		

		//TODO: algorithme

		return 0; 
	//}
}
