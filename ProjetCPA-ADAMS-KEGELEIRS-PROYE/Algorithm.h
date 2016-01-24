#include <iostream>
#include <string>
#include <vector>
#include "Blosum.h"
#include "Sequence.h"

class Algorithm
{
private:
	Blosum* blosum; //score matrix
	int gapOpenPenalty; //gap open penalty
	int gapExtensionPenalty; //gap extend penalty
	std::vector<int> seqId; //id's of the best scoring sequences
	std::vector<int> score; //score of the best scoring sequences

	int blosumScore(char a, char b, std::string residues, int matrix[][24]) const;
	int findMax(int a, int b, int c) const;
	int findMax(int a, int b) const;
	int findMin(std::vector<int> vec) const;
	void getScore(Database* db, Sequence* query, Blosum* blosum, int gop, int gep, Algorithm* algo);
	
public:
	Algorithm(Database* db, Sequence* query, Blosum* blosum, int gapOpenPenalty, int gapExtensionPenalty);
	Blosum* getBlosum() const;
	int getGOP() const;
	int getGEP() const;
	std::vector<int> getSeqId() const;
	std::vector<int> getScore() const;
	void setBlosum(Blosum* new_blosum);
	void setGOP(int gop);
	void setGEP(int gep);
	void setSeqId(std::vector<int> new_seqId);
	void setScore(std::vector<int> new_scores);
	
};
