#include "Sequence.h"

using namespace std;

//getters
string Sequence::getChain() const
{
	return chain;
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

//setters	
void Sequence::setChain(string new_chain)
{	
	chain = new_chain;
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

//used in the reading of header file to check the end of a sequence or a choice
int Sequence::checkEnd(unsigned char* buffer, int cursor) const
{
	return (unsigned int)buffer[cursor]+(unsigned int)buffer[cursor+1];
}

//decode a big endian any byte long hex number ans gives its int value
unsigned long Sequence::decodeAny(vector<unsigned char> buf) const
{
	unsigned long result = 0;
	int size = buf.size(); //gets number of bytes
	for(int i=0; i<size;i++)  //reads the number
		result += buf[size-1-i]*pow(16,2*i);
	return result;	
}

//init Sequence attributes by reading recursively the header file. Needs the offsets of the sequence's header (pos)
int Sequence::getHeader(unsigned char* buffer, int pos, Sequence* seq)
{
	if(pos >= 0) //checks if offsets is relevant
	{		
		vector<unsigned char> int_buf; //variable size byte buffer
		int cursor = pos; //gives the position in the file
		unsigned int int_length; //int length buffer
		unsigned long string_length; //string length buffer
		unsigned int nb_byte; //number of bytes of an entry

		if((unsigned int)buffer[cursor] == 2) //if read byte indicates an integer
		{
			cursor++;	//moves cursor
			int_length = (unsigned int)buffer[cursor]; //reads the length of the integer
			cursor++;   
			for(int j=cursor;j<cursor+int_length; j++) //reads and decodes integer
				int_buf.push_back(buffer[j]);
			cursor += int_length;
			unsigned long number = decodeAny(int_buf);
			int_buf.clear(); //clear the buffer
			if(seq->getId() == -1)	//first int to init is id
				seq->setId(number);	
			return cursor;
		}
		else if((unsigned int)buffer[cursor] == 26) //if read byte indicates a string
		{
			cursor++;  //moves cursor
			string words = ""; //string buffer
			if((unsigned int)buffer[cursor] <= 128) //if string is 128bits long maximum
			{
				string_length = (unsigned long)buffer[cursor]; //reads the length directly
				cursor++;
			}
			else                                     //if string longer than 128 bits
			{
				nb_byte = (unsigned int)buffer[cursor]-128; //reads number of byte of the length integre
				cursor++;
				for(int j=cursor;j<cursor+nb_byte; j++) //reads and decodes length
					int_buf.push_back(buffer[j]);
				cursor += nb_byte;
				string_length = decodeAny(int_buf);
				int_buf.clear();                       //clear buffer
			}	
			for(int j=cursor;j<(cursor+string_length); j++) //reads the string
				 words += buffer[j];
			cursor += string_length;
			if(seq->getDescription() == "") //first string to init is description
				seq->setDescription(words);
			else if(seq->getIdInfo() == "") //second to init is idInfo
				seq->setIdInfo(words);
			return cursor;
		}
		else if(((unsigned int)buffer[cursor] == 48) && ((unsigned int)buffer[cursor+1] == 128)) // if read byte indicates a sequence
		{
			cursor +=  2;
			cursor = getHeader(buffer, cursor, seq); //recursively reads sequence's content
			if(checkEnd(buffer, cursor) == 0) //checks sequence's end
				return cursor+2;
			else
				return -1;
		}
		else if(((unsigned int)buffer[cursor] >= 160) && ((unsigned int)buffer[cursor+1] == 128)) // if read byte indicates a choice
		{
			cursor += 2;
			cursor =  getHeader(buffer, cursor, seq); //recursively read the choice's content
			if((checkEnd(buffer, cursor) == 0) && (checkEnd(buffer, cursor+2) == 0)) //checks end of choices
				return cursor+2;
			else if(checkEnd(buffer, cursor) == 0) //checks if there is another choice
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

//inits sequence by reading the fasta file
void Sequence::readFasta(const char* fileName, Sequence* seq)
{
	ifstream file(fileName, ios::in);
	if(file)
	{
		string line;
		getline(file, line); //first line is description
		seq->setDescription(line);
		string chain = "";
		while(getline(file, line)) //rest of the lines are the chain of residues
			chain += line;
		seq->setChain(chain);
		int length = chain.size();
		seq->setLength(length);	
	}

}

//constructor reading database content
Sequence::Sequence(unsigned char* buffer, Database* db, int pos) 
{
	this->setId(-1);
	this->setDescription("");
	this->setIdInfo("");	
	if(this->getHeader(buffer, db->getHeaderOffsets()[pos], this) == -1)
		cout << "Error. Can't init sequence" << endl;
	this->setChain(db->getSequences()[pos]);
	this->setLength(chain.size());		
}

//constructor reading fasta file
Sequence::Sequence(const char* fileName)
{
	this->readFasta(fileName, this);
	this->setId(-1);
	this->setIdInfo("");
}


