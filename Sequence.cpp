#include "Sequence.h"

using namespace std;

Sequence::Sequence(string name, int lenght, string description) 
{
	name = name;
	lenght = length;
	description = description;	
}

string Sequence::getName() const
{
	return name;
}

int Sequence::getLength() const
{
	return length;
}

string Sequence::getDescription() const
{
	return description;
}	
void Sequence::setName(string name)
{	
	name = name;
}

void Sequence::setLength(int length)
{
	length=length;
}

void Sequence::setDescription(string description)
{
	description=description;
}
int Sequence::compareTo(Sequence seq)
{
}
