#include "Sequence.h"

using namespace std;

string Sequence::getName() const
{
	return name;
}

int Sequence::getLength() const
{
	return length;
}

int Sequence::getId() const
{
	return id;
}

string Sequence::getIdInfo() const
{
	return idInfo;
}

string Sequence::getDescription() const
{
	return description;
}	
void Sequence::setName(string new_name)
{	
	name = new_name;
}

void Sequence::setLength(int new_length)
{
	length = new_length;
}

void Sequence::setId(int new_id)
{
	id = new_id;
}

void Sequence::setIdInfo(string id_info)
{
	idInfo = id_info;
}

void Sequence::setDescription(string new_description)
{
	description = new_description;
}

int Sequence::checkEnd(unsigned char* buffer, int cursor) const
{
	return (unsigned int)buffer[cursor]+(unsigned int)buffer[cursor+1];
}

unsigned long Sequence::decodeAny(vector<unsigned char> buf) const
{
	unsigned long result = 0;
	int size = buf.size();
	for(int i=0; i<size;i++)
		result += buf[size-1-i]*pow(16,2*i);
	return result;	
}


int Sequence::getHeader(unsigned char* buffer, int pos, Sequence* seq)
{
	if(pos >= 0)
	{		
		vector<unsigned char> int_buf;
		int cursor = pos;
		unsigned int int_length; 
		unsigned long string_length;
		unsigned int nb_byte;

		if((unsigned int)buffer[cursor] == 2)
		{
			cursor++;
			int_length = (unsigned int)buffer[cursor];
			cursor++;
			for(int j=cursor;j<cursor+int_length; j++)
				int_buf.push_back(buffer[j]);
			cursor += int_length;
			unsigned long number = decodeAny(int_buf);
			int_buf.clear();
			if(seq->getId() == -1)
				seq->setId(number);	
			return cursor;
		}
		else if((unsigned int)buffer[cursor] == 26)
		{
			cursor++;
			string words = "";
			if((unsigned int)buffer[cursor] <= 128)
			{
				string_length = (unsigned long)buffer[cursor];
				cursor++;
			}
			else
			{
				nb_byte = (unsigned int)buffer[cursor]-128;
				cursor++;
				for(int j=cursor;j<cursor+nb_byte; j++)
					int_buf.push_back(buffer[j]);
				cursor += nb_byte;
				string_length = decodeAny(int_buf);
				int_buf.clear();
			}	
			for(int j=cursor;j<(cursor+string_length); j++)
				 words += buffer[j];
			cursor += string_length;
			if(seq->getDescription() == "")
				seq->setDescription(words);
			else if(seq->getIdInfo() == "")
				seq->setIdInfo(words);
			return cursor;
		}
		else if(((unsigned int)buffer[cursor] == 48) && ((unsigned int)buffer[cursor+1] == 128))
		{
			cursor +=  2;
			cursor = getHeader(buffer, cursor, seq);
			if(checkEnd(buffer, cursor) == 0)
				return cursor+2;
			else
				return -1;
		}
		else if(((unsigned int)buffer[cursor] >= 160) && ((unsigned int)buffer[cursor+1] == 128))
		{
			cursor += 2;
			cursor =  getHeader(buffer, cursor, seq);
			if((checkEnd(buffer, cursor) == 0) && (checkEnd(buffer, cursor+2) == 0))
				return cursor+2;
			else if(checkEnd(buffer, cursor) == 0)
				return getHeader(buffer, cursor+2, seq);
			else 
				return -1;
		}
		else
			return -1;
	}
	else
		return -1;		
}

Sequence::Sequence(unsigned char* buffer, int pos) 
{
	this->setId(-1);
	this->setDescription("");
	this->setIdInfo("");	
	if(this->getHeader(buffer, pos, this) == -1)
		cout << "Error. Can't init sequence" << endl;		
}


int Sequence::compareTo(Sequence seq)
{
}
