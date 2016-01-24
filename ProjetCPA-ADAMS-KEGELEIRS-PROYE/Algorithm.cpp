#include "Algorithm.h"
using namespace std;

//constructor
Algorithm::Algorithm(Database* db, Sequence* query, Blosum* blosum, int gapOpenPenalty, int gapExtensionPenalty)
{
	this->setBlosum(blosum);
	this->setGOP(gapOpenPenalty);
	this->setGEP(gapExtensionPenalty);
	this->getScore(db, query, blosum, gapOpenPenalty, gapExtensionPenalty, this);
}

//gets the score of an allignement reading the score matrix
int Algorithm::blosumScore(char a,char b, string residues, int matrix[][24]) const
{
	int result;
	int line;
	int column;
	if((a==' ') || (b==' '))
		return -1;
	else
	{
		for (int i=0; i<24; i++)
		{	
			if (a==residues[i]) //searchs query sequence residue in the table
				line = i;
			if (b==residues[i]) //searchs database sequence residue in the table
				column = i;
		}
		result = matrix[line][column];
		return result;
	}
}	

//gets the max of 3 values
int Algorithm::findMax(int a, int b, int c) const
{
	int max = a;
	if(max<b)
		max = b;
	if(max<c)
		max = c;
	return max;
}

//gets the max of two values	
int Algorithm::findMax(int a, int b) const
{
	int max = a;
	if(b>a)
		max = b;
	return max;	
}

//gets the position of the minimum of a vector
int Algorithm::findMin(vector<int> vec) const
{
	int min_pos = 0;
	for(int i = 1; i < vec.size(); i++)
	{
		if(vec[min_pos] > vec[i])
			min_pos = i;
	}
	return min_pos;	
}


//gets the scores comparing query sequence to database sequences
void Algorithm::getScore(Database* db, Sequence* query, Blosum* blosum, int gop, int gep, Algorithm* algo)
{
	string query_chain = query->getChain();
	int size = query_chain.size();
	int length = db->getSequences().size();
	int R = gep;
	int Q = gop;
	int S; //local score
	int min_pos;
	vector<int> score; //vector of scores
	vector<int> ids; //vector of sequence id's
	char a, b;
	int matrix[24][24];
	blosum->cpyMatrix(matrix);
	string residues = blosum->getResidues(); //conversion table for score matrix
	for(int k=0; k<length;k++)
	{
		int* H = new int[size];   //init of calculation's parameters
		int* E = new int[size];
		int* F = new int[size];
		int* BH = new int[size];
		int* BE = new int[size];
		int* BF = new int[size];
		int* swap;
		S = 0;
		string current_seq = db->getSequences()[k];
		if(current_seq.size() != 0)
		{
			for(int j=0;j<current_seq.size();j++) // calculation
			{
				b = current_seq[j];	
				for(int i=0;i<size;i++)
				{
					a = query_chain[i];
					if((i==0) && (j==0))
					{
						F[i]=0;
						E[i]=0;	
						H[i]=findMax(blosumScore(a,b,residues,matrix), 0);
					}
					else if((i==0) && (j!=0))
					{
						F[i]=0;
						E[i]=findMax(BH[i]-Q, BE[i]-R, 0);
						H[i]=findMax(blosumScore(a,b,residues,matrix),E[i],F[i]);
					}
					else if((i!=0) && (j==0))
					{
						F[i] = findMax(H[i-1]-Q, F[i-1]-R, 0);
						E[i] = 0;
						H[i] = findMax(blosumScore(a,b,residues,matrix),E[i],F[i]);
					}	
					else
					{
						F[i] = findMax(H[i-1]-Q, F[i-1]-R, 0);
						E[i] = findMax(BH[i]-Q, BE[i]-R, 0);
						H[i] = findMax(BH[i-1] + blosumScore(a,b,residues,matrix),E[i],F[i]);
						if(H[i]>S)
							S=H[i];
					}
				}
			swap = BH;  //swap actual values with saved values
			BH = H;
			H = swap;
			swap = BE;
			BE = E;
			E = swap;
			swap = BF;
			BF = F;
			F = swap;
			}
			if(score.size() == 100) //no more than 100 scores, gets the best ones
			{
				min_pos = findMin(score);
				if(S > score[min_pos])
				{
					score[min_pos] = S;
					ids[min_pos] = k;
				}
			}
			else
			{
				score.push_back(S);
				ids.push_back(k);
			}
		}
		delete [] H;
		delete [] E;
		delete [] F;
		delete [] BH;
		delete [] BE;
		delete [] BF;
		
	}
	algo->setScore(score);	
	algo->setSeqId(ids);							
}

//getters
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

//setters
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
