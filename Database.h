#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "Sequence.h"

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
	void init(unsigned char* buffer, Database* db);
	unsigned long decode32(unsigned char* buf) const;
	unsigned long decode64(unsigned char* buf) const;

public:
	Database(const char* fileName);
	std::string getFileName() const;
	std::string getTitle() const;
	unsigned long getResiduesSize() const;
	unsigned long getSequenceSize() const;
	unsigned long getLongestSeq() const;
	std::vector<unsigned long> getHeaderOffsets() const;
	std::vector<unsigned long> getSeqOffsets() const;
	void setFileName(std::string name);
	void setTitle(std::string title);
	void setResiduesSize(unsigned long residue_nb);
	void setSequenceSize(unsigned long seq_nb);
	void setLongestSeq(unsigned long max_seq);
	void setHeaderOffsets(std::vector<unsigned long> header_offsets);
	void setSeqOffsets(std::vector<unsigned long> seq_offsets);
	Sequence seekSequence();
};
