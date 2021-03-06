#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

void init_blosum(int Matrix[][24], string &residues, const char* fileName)
{
	ifstream file(fileName, ios::in);
	if(file)
	{
		string line;
		char a;
		int b;
		while((getline(file,line)) && (line[0] == '#')){}
		for(int j=0; j< 24; j++)
		{
			file >> a;
			residues += a;
			for(int i=0; i<24;i++)
			{
				file >> b;
				Matrix[i][j] = b;
			}
		}
				
			
	}

}


double blosum_score(char a,char b, string letters, matrix[][])
{
	double result;
	int line;
	int column;
	for (int i=0; i<24; i++)
	{
		if (a==letters[i])
			line == i;
		if (b==letters[i])
			column == i;
	}
	result = matrix[line][column];
	return result;
}
	
	
double find_max(double array[], int length)
{
	double max = array[0];
	for(int i=1; i<length; i++)
	{
		if(array[i] > max)
			max = array[i];
	}
	return max;
}


int main()
{
	string residues = "";
	int BlosumMatrix[24][24];
	init_blosum(Matrix, residues,"/home/student/Bureau/BLOSUM62");

	double delta;
	string seq_a = "aaaaaaaa";
	string seq_b = "ababaab";
	int length_a = seq_a.size();
	int length_b = seq_b.size();
	
	double M[length_a+1][length_b+1];
	for(int i=0; i<=length_a; i++)
	{
		for(int j=0; j<=length_b; j++)
			M[i][j] = 0;
	}
	
	double options[4];
	for(int i=1; i<=length_a; i++)
	{
		for(int j=1; j<=length_b; j++)
		{
			options[0] = M[i-1][j-1] + blosum_score(seq_a[i-1], seq_b[j-1], residues, BlosumMatrix);
			options[1] = M[i-1][j] - delta;
			options[2] = M[i][j-1] - delta;
			options[3] = 0;
			M[i][j] = find_max(options,4);
		}
	}
	
	for(int i=1; i<=length_a; i++)
	{
		for(int j=1; j<=length_b; j++)
			cout << M[i][j] <<" ";
	}
	
	double M_max = 0;
	for(int i=1; i<=length_a; i++)
	{
		for(int j=1; j<=length_b; j++)
		{
			if(M[i][j] > M_max)
			{
				M_max = M[i][j];
			}
		}
	}
	cout << M_max << endl;
}

