#include "Blosum.h"

using namespace std;

//constructor
Blosum::Blosum(const char* fileName)
{
	int Matrix[24][24];
	string residues;
	this->initBlosum(Matrix, residues, fileName, this);	
}

//inits attributes by reading de score matrix file
void Blosum::initBlosum(int Matrix[][24], string &residues, const char* fileName, Blosum* blosum)
{
	ifstream file(fileName, ios::in);
	if(file)
	{
		string line;
		char a;
		int b;
		while((getline(file,line)) && (line[0] == '#')){} //skips the comments lines
		for(int j=0; j< 24; j++)
		{
			file >> a;   //read first char to init conversion table
			residues += a;
			for(int i=0; i<24;i++)
			{
				file >> b;  //reads rest of the int to init the score matrix
				this->Matrix[i][j] = b;
			}
		}
		this->setResidues(residues);			
	}
}

//getter
string Blosum::getResidues() const
{
	return residues;
}

//setter
void Blosum::setResidues(string newResidues)
{
	residues = newResidues;
}

//copies matrix to a local matrix variable
void Blosum::cpyMatrix(int matrix[][24])
{
	for(int j=0;j<24;j++)
	{
		for(int i=0;i<24;i++)
			matrix[i][j] = Matrix[i][j];
	}
}
