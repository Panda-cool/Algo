#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

class Sequence
{
private:
	std::string name;
	int length;
	int id;
	std::string idInfo;
	std::string description;

	int getHeader(unsigned char* buffer, int pos, Sequence* seq);
	unsigned long decodeAny(std::vector<unsigned char> buf) const;
	int checkEnd(unsigned char* buffer, int cursor) const;

public:
	Sequence(unsigned char* buffer, int pos);
	std::string getName() const;
	int getLength() const;
	int getId() const;
	std::string getIdInfo() const;
	std::string getDescription() const;
	void setName(std::string new_name);
	void setLength(int new_length);
	void setId(int new_id);
	void setIdInfo(std::string id_info);
	void setDescription(std::string new_description);
	int compareTo(Sequence seq);
};
