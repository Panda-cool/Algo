#include "Database.h"

using namespace std;


unsigned long Database::decode32(unsigned char* buf) const
{	
	return pow(16,6)*(unsigned long)buf[0] + pow(16,4)*(unsigned long)buf[1] + pow(16,2)*(unsigned long)buf[2] + (unsigned long)buf[3];
}

unsigned long Database::decode64(unsigned char* buf) const
{
	return (unsigned long)buf[0] + pow(16,2)*(unsigned long)buf[1] + pow(16,4)*(unsigned long)buf[2] + pow(16,6)*(unsigned long)buf[3] + pow(16,8)*(unsigned long)buf[4] + pow(16,10)*(unsigned long)buf[5] + pow(16,12)*(unsigned long)buf[6] + pow(16,14)*(unsigned long)buf[7];
}


string Database::getFileName() const
{
	return fileName;
}

string Database::getTitle() const
{
	return title;
}

unsigned long Database::getResiduesSize() const
{
	return residuesSize;
}

unsigned long Database::getSequenceSize() const
{
	return sequenceSize;
}

unsigned long Database::getLongestSeq() const
{
	return longestSeq;
}

vector<unsigned long> Database::getHeaderOffsets() const
{
	return headerOffsets;
}

vector<unsigned long> Database::getSeqOffsets() const
{
	return seqOffsets;
}

void Database::setFileName(string name)
{
	fileName = name;
}

void Database::setTitle(string ptitle)
{
	title = ptitle;
}

void Database::setResiduesSize(unsigned long residue_nb)
{
	residuesSize = residue_nb;
}

void Database::setSequenceSize(unsigned long seq_nb)
{
	sequenceSize = seq_nb;
}

void Database::setLongestSeq(unsigned long max_seq)
{
	longestSeq = max_seq;
}

void Database::setHeaderOffsets(vector<unsigned long> header_offsets)
{
	headerOffsets = header_offsets;
}

void Database::setSeqOffsets(vector<unsigned long> seq_offsets)
{
	seqOffsets = seq_offsets;
}


void Database::init(unsigned char* buffer, Database* db)
{
	unsigned char data_buf[4];
	unsigned char big_data_buf[8];
	int cursor = 4;
	string title;
	vector<unsigned long> header_offsets;
	vector<unsigned long> seq_offsets;

	for(int j = cursor; j<cursor+4; j++)
		data_buf[j-cursor]= buffer[j];
	cursor += 4;	
	unsigned long data_type  = decode32(data_buf);	
	if(data_type == 1)
	{
		for(int j = cursor; j<cursor+4; j++)
			data_buf[j-cursor]= buffer[j];
		cursor += 4;
		unsigned long title_length = decode32(data_buf);
		for(int j = cursor; j<cursor+title_length; j++)
			title += buffer[j];
		cursor += title_length;
		for(int j = cursor; j<cursor+4; j++)
			data_buf[j-cursor]= buffer[j];	
		unsigned long timestamp_length = decode32(data_buf);
		cursor += (4+timestamp_length);
		for(int j = cursor; j<cursor+4; j++)
			data_buf[j-cursor]= buffer[j];
		cursor += 4;	
		unsigned long seq_nb = decode32(data_buf);
		for(int j = cursor; j<cursor+8; j++)
			big_data_buf[j-cursor] = buffer[j];
		cursor += 8;
		unsigned long residue_nb = decode64(big_data_buf);	
		for(int j = cursor; j<cursor+4; j++)
			data_buf[j-cursor] = buffer[j];
		cursor += 4;
		unsigned long max_seq = decode32(data_buf);
		int cursor_aux = 0;
		for(int j = cursor; j<cursor+4+(4*seq_nb); j++)
		{
			data_buf[cursor_aux] = buffer[j];
			cursor_aux++;
			if(cursor_aux >3)
			{
				cursor_aux = 0;
				header_offsets.push_back(decode32(data_buf));
			}
		}
		cursor += (4+4*seq_nb);
		for(int j = cursor; j<cursor+4+(4*seq_nb); j++)
		{
			data_buf[cursor_aux] = buffer[j];
			cursor_aux++;
			if(cursor_aux >3)
			{
				cursor_aux = 0;
				seq_offsets.push_back(decode32(data_buf));
			}
		}
		cursor += (4+4*seq_nb);
		db->setTitle(title);
		db->setResiduesSize(residue_nb);
		db->setSequenceSize(seq_nb);
		db->setLongestSeq(max_seq);
		db->setHeaderOffsets(header_offsets);
		db->setSeqOffsets(seq_offsets);
	}	
}

Database::Database(const char* fileName)
{
	ifstream file(fileName, ios::binary);
	if(file)
	{
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);
		unsigned char* buffer = new unsigned char[length];
		file.read((char*)buffer, length);

		this->init(buffer, this);
	}
}



Sequence Database::seekSequence()
{
}

