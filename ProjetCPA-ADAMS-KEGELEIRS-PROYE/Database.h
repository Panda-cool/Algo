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
	std::string title; //title of the database
	unsigned long residuesSize; //number of residues in the database
	unsigned long sequenceSize; //number of sequences in the database
	unsigned long longestSeq; //number of residues in the longest sequence in the database	
	std::vector<unsigned long> headerOffsets; //list of offsets in the header file
	std::vector<unsigned long> seqOffsets; //list of offsets in the sequence file
	std::vector<std::string> sequences; //list of sequences in the sequence file

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
