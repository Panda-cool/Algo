#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "Database.h"

class Sequence
{
private:
	std::string chain; //the protein sequence represents by its residues
	int length; //length of the sequence
	int id; //id of the sequence
	std::string idInfo; //info about the id
	std::string description; //description and name of the protein

	int getHeader(unsigned char* buffer, int pos, Sequence* seq);
	unsigned long decodeAny(std::vector<unsigned char> buf) const;
	int checkEnd(unsigned char* buffer, int cursor) const;
	void readFasta(const char* fileName, Sequence* seq);

public:
	Sequence(unsigned char* buffer, Database* db, int pos);
	Sequence(const char* fileName);
	std::string getChain() const;
	int getLength() const;
	int getId() const;
	std::string getIdInfo() const;
	std::string getDescription() const;
	void setChain(std::string new_name);
	void setLength(int new_length);
	void setId(int new_id);
	void setIdInfo(std::string id_info);
	void setDescription(std::string new_description);
};
