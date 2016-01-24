#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <math.h>


using namespace std;

int length;
unsigned char data_buf[4];
unsigned char big_data_buf[8];
string title;
int cursor;
vector<unsigned long> header_offsets;
vector<unsigned long> seq_offsets;
vector<unsigned char> int_buf;


unsigned long decode32(unsigned char* buf)
{	
	return pow(16,6)*(unsigned long)buf[0] + pow(16,4)*(unsigned long)buf[1] + pow(16,2)*(unsigned long)buf[2] + (unsigned long)buf[3];
}

unsigned long decode64(unsigned char* buf)
{
	return (unsigned long)buf[0] + pow(16,2)*(unsigned long)buf[1] + pow(16,4)*(unsigned long)buf[2] + pow(16,6)*(unsigned long)buf[3] + pow(16,8)*(unsigned long)buf[4] + pow(16,10)*(unsigned long)buf[5] + pow(16,12)*(unsigned long)buf[6] + pow(16,14)*(unsigned long)buf[7];
}

unsigned long decode_any(vector<unsigned char> buf)
{
	unsigned long result = 0;
	int size = buf.size();
	for(int i=0; i<size;i++)
		result += buf[size-1-i]*pow(16,2*i);
	return result;	
}

char get_residue(unsigned int value)
{
	if(value > 27)
		return '-';
	else
	{
		char residues[] = "-ABCDEFGHIKLMNPQRSTVWXYZU*OJ";
		return residues[value];
	}
}

int check_end(unsigned char* buffer, int cursor)
{
	return (unsigned int)buffer[cursor]+(unsigned int)buffer[cursor+1];
}

int get_header(unsigned char* buffer, int pos)
{
	if(pos >= 0)
	{
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
			unsigned long number = decode_any(int_buf);
			int_buf.clear();
			cout << number << endl;
			return cursor;
		}
		else if((unsigned int)buffer[cursor] == 26)
		{
			cursor++;
			string word = "";
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
				string_length = decode_any(int_buf);
				int_buf.clear();
			}	
			for(int j=cursor;j<(cursor+string_length); j++)
				 word += buffer[j];
			cursor += string_length;
			cout << word << endl;
			return cursor;
		}
		else if(((unsigned int)buffer[cursor] == 48) && ((unsigned int)buffer[cursor+1] == 128))
		{
			cursor +=  2;
			cursor = get_header(buffer, cursor);
			if(check_end(buffer, cursor) == 0)
				return cursor+2;
			else
				return -1;
		}
		else if(((unsigned int)buffer[cursor] >= 160) && ((unsigned int)buffer[cursor+1] == 128))
		{
			cursor += 2;
			cursor =  get_header(buffer, cursor);
			if((check_end(buffer, cursor) == 0) && (check_end(buffer, cursor+2) == 0))
				return cursor+2;
			else if(check_end(buffer, cursor) == 0)
				return get_header(buffer, cursor+2);
			else 
				return -1;
		}
		else
			return -1;
	}
	else
		return -1;	
		
}

vector<string> get_seq(unsigned char* buffer)
{
	vector<string> sequences;
	string string_buf = "";

	for(int j=0;j<length;j++)
	{
		if((unsigned int)buffer[j] != 0)
			string_buf += get_residue((unsigned int)buffer[j]);
		else
		{
			sequences.push_back(string_buf);
			string_buf = "";
		}
	}
	return sequences;
}

vector<unsigned long> get_pin(unsigned char* buffer)
{
	unsigned char data_buf[4];
	unsigned char big_data_buf[8];
	string title;
	vector<unsigned long> header_offsets;
	vector<unsigned long> seq_offsets;

	int cursor = 4;
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
		cout << header_offsets[25] <<endl;
		cout << seq_offsets[48] << endl;
		return header_offsets;
	}	
}
int main()
{
	ifstream file("/home/student/Documents/algo/uniprot_sprot.fasta.pin", ios::binary);
	ifstream file2("/home/student/Documents/algo/uniprot_sprot.fasta.psq", ios::binary);
	ifstream file3("/home/student/Documents/algo/uniprot_sprot.fasta.phr", ios::binary);

	
	if(file)
	{
		file.seekg(0, file.end);
		length = file.tellg();
		file.seekg(0, file.beg);
		unsigned char* buffer = new unsigned char[length];
		file.read((char*)buffer, length);
		
		header_offsets = get_pin(buffer);
		
	}
	if(file2)
	{
		file2.seekg(0, file2.end);
		length = file2.tellg();
		file2.seekg(0, file2.beg);
		unsigned char* buffer = new unsigned char[length];
		file2.read((char*)buffer, length);
		vector<string> sequences = get_seq(buffer);
			
		cout << sequences[5] << endl;
		cout << sequences[258] << endl;

	}
	if(file3)
	{
		file3.seekg(0, file3.end);
		length = file3.tellg();
		file3.seekg(0, file3.beg);
		unsigned char* buffer = new unsigned char[length];
		file3.read((char*)buffer, length);
		
		if(get_header(buffer,(int)header_offsets[0] ) >= 0)
			cout << "ok" << endl;
		else
			cout << "not ok" << endl;

	}


}		
