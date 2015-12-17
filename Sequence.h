#include <string>
#include <stdio.h>

class Sequence
{
private:
	std::string name;
	int length;
	std::string description;

public:
	Sequence(std::string name, int lenght, std::string description);
	std::string getName() const;
	int getLength() const;
	std::string getDescription() const;
	void setName(std::string name);
	void setLength(int length);
	void setDescription(std::string description);
	int compareTo(Sequence seq);
};
