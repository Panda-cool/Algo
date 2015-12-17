#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>

class Database 
{
private:
	std::string fileName;
	std::string title;
	unsigned long residuesSize;
	unsigned long sequenceSize;
	unsigned long longestSeq;	
	std::vector<unsigned long> headerOffsets;
	std::vector<unsigned long> seqOffsets;
	std::vector<std::string> sequences;

	void initIndex(unsigned char* buffer, Database* db);
	void initSeq(unsigned char* buffer, int length, Database* db);
	unsigned long decode32(unsigned char* buf) const;
	unsigned long decode64(unsigned char* buf) const;
	char getResidue(unsigned int value) const;

public:
	Database(const char* indexName, const char* seqName);
	std::string getFileName() const;
	std::string getTitle() const;
	unsigned long getResiduesSize() const;
	unsigned long getSequenceSize() const;
	unsigned long getLongestSeq() const;
	std::vector<unsigned long> getHeaderOffsets() const;
	std::vector<unsigned long> getSeqOffsets() const;
	std::vector<std::string> getSequences() const;
	void setFileName(std::string name);
	void setTitle(std::string title);
	void setResiduesSize(unsigned long residue_nb);
	void setSequenceSize(unsigned long seq_nb);
	void setLongestSeq(unsigned long max_seq);
	void setHeaderOffsets(std::vector<unsigned long> header_offsets);
	void setSeqOffsets(std::vector<unsigned long> seq_offsets);
	void setSequences(std::vector<std::string> sequences);
};
