#include "Sequence.h"

using namespace std;

Sequence::Sequence(string name, int lenght, string description) 
{
	name = name;
	lenght = lenght;
	description = description;	
}

string Sequence::getName()
{
	return name;
}

int Sequence::getLenght()
{
	return lenght;
}

string Sequence::getDescription()
{
	return description;
}	
void Sequence::setName(string name)
{	
	name = name;
}

void Sequence::SetLenght(int lenght)
{
	lenght=lenght
}

void Sequence::SetDescription(string description)
{
	description=description
}
int Sequence::compareTo(Sequence seq)
{
}
