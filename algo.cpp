#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

double blossum_score(char a,char b)
{
	return 0;
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
			options[0] = M[i-1][j-1] + blossum_score(seq_a[i-1], seq_b[j-1]);
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
	int i_max = 0;
	int j_max = 0;
	for(int i=1; i<=length_a; i++)
	{
		for(int j=1; j<=length_b; j++)
		{
			if(M[i][j] > M_max)
			{
				M_max = M[i][j];
				i_max = i;
				j_max = j;
			}
		}
	}
	cout << M_max << endl;
}

