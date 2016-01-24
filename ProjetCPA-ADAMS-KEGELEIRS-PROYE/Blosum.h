#include <string>
#include <iostream>
#include <fstream>

class Blosum
{
private:
	std::string residues; //border of the matrix containing the reading table
	int Matrix[24][24]; //score matrix
	void initBlosum(int Matrix[][24], std::string &residues, const char* fileName, Blosum* blosum);
public:
	
	Blosum(const char* fileName);
	std::string getResidues() const;
	void setResidues(std::string newResidues);
	void cpyMatrix(int matrix[][24]);
};
