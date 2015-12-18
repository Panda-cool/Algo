#include <iostream>
#include <string>
#include <vector>
#include "Blossum.h"
#include "Database.h"
#include "Sequence.h"

class Algorithm
{
private:
	Blosum* blosum;
	int gapOpenPenalty;
	int gapExtensionPenalty;
	std::vector<int> seqId;
	std::vector<int> scores;

	double blosumScore(char a, char b, std::string residues, int Matrix[][]) const;
	double findMax(double array[], int length) const;
	void getScore(Database* db, Sequence* query);
	
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
	void setScores(std::vector<int> new_scores);
	
};
