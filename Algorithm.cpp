#include "Algorithm.h"

using namespace std;

Algorithm::Algorithm(Database* db, Sequence* query, Blosum* blosum, int gapOpenPenalty, int gapExtensionPenalty)
{
	this->setBlosum(blosum);
	this->setGOP(gapOpenPenalty);
	this->setGEP(gapExtensionPenalty;
	this->getScore(db, query);
}

double Algorithm::blosumScore(char a,char b, string residues, int Matrix[][]) const
{
	double result;
	int line;
	int column;
	for (int i=0; i<24; i++)
	{
		if (a==letters[i])
			line == i;
		if (b==letters[i])
			column == i;
	}
	result = matrix[line][column];
	return result;
}

double Algorithm::findMax(double array[], int length) const
{
	double max = array[0];
	for(int i=1; i<length; i++)
	{
		if(array[i] > max)
			max = array[i];
	}
	return max;
}

void Algorithm::getScore(Database* db, Sequence* query)
{
	string query_chain = query->getChain();
	int length = db->getSequences().size();
}

Blosum* Algorithm::getBlosum() const
{
	return blosum;
}

int Algorithm::getGOP() const
{
	return gapOpenPenalty;
}

int Algorithm::getGEP() const
{
	return gapExtensionPenalty;
}

vector<int> Algorithm::getSeqId() const
{
	return seqId;
}

vector<int> Algorithm::getScore() const
{
	return score;
}

void Algorithm::setBlosum(Blosum* new_blosum)
{
	blosum = new_blosum;
}

void Algorithm::setGOP(int gop)
{
	gapOpenPenalty = gop;
}

void Algorithm::setGEP(int gep)
{
	gapExtensionPenalty = gep;
}

void Algorithm::setSeqId(vector<int> new_seqId)
{
	seqId = new_seqId;
}
void Algorithm::setScore(vector<int> new_score)
{
	score = new_score;
}
