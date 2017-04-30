#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include "Header.h"
using namespace std;

int main()
{

	string file1, file2;
	int n, n1,count;
	cin >> file1;
	cin >> file2;
	cout << "Iput filenames, whithout '.txt':" << endl;
	file1 += ".txt";
	file2 += ".txt";
	ifstream infile1(file1.c_str());
	ifstream infile2(file2.c_str());
	if (!infile1 || !infile2)
	{
		cout << "Error! File not found!" << endl;
		return NULL;
	}
	infile1 >> n;
	infile2 >> n1;
	if (n == '\0' && n1 == '\0' || n < 2) return 99;
	float ** numarray = new float *[n];
	float * numarray1 = new float[n1];
	float * rezline;
	for (int r = 0; r < n; r++)
	{
		numarray[r] = new float[1];
		for (int c = 0; c < 2; c++)
		{
			infile1 >> numarray[r][c];
		}
	}
	for (int i = 0; i<n1; i++)
	{
		infile2 >> numarray1[i];
	}
	infile1.close();
	infile2.close();
	Sort(numarray, n);
	Sort(numarray1, n1);
	cout << "Choose interpolation: 1-linear, 2-quadric, 3-cubic, 4-all." <<endl;
	cout << "Or press any key to exit." << endl;
	cin >> count;
	switch (count) 
	{
	case 1: 
	{
		rezline = lineinterpol(numarray, numarray1, n, n1);
		ofstream out("rezline.txt");
		out << rezline[0]-1 << endl;
		for (int i = 1, j=0; i < rezline[0]; i++, j++)
		{
			out << numarray1[j] << ' ' << rezline[i] << endl;
		}
		out.close();
		break;
	}
	case 2: 
	{
		rezline = quadinterpol(numarray, numarray1, n, n1);
		ofstream out("rezquad.txt");
		out << rezline[0] - 1 << endl;
		for (int i = 1, j = 0; i < rezline[0]; i++, j++)
		{
			out << numarray1[j] << ' ' << rezline[i] << endl;
		}
		out.close();
		break;
	}
	case 3: 
	{
		rezline = cubicinterpol(numarray, numarray1, n, n1);
		ofstream out("rezcubic.txt");
		out << rezline[0] - 1 << endl;
		for (int i = 1, j = 0; i < rezline[0]; i++, j++)
		{
			out << numarray1[j] << ' ' << rezline[i] << endl;
		}
		out.close();
		break;
	}
	case 4: 
	{
		rezline=lineinterpol(numarray, numarray1, n, n1);
		ofstream out("rezall.txt");
		out << rezline[0] - 1 << endl;
		for (int i = 1, j = 0; i < rezline[0]; i++, j++)
		{
			out << numarray1[j] << ' ' << rezline[i] << endl;
		}
		out << "--------Linear--------" << endl;
		rezline = quadinterpol(numarray, numarray1, n, n1);
		out << rezline[0] - 1 << endl;
		for (int i = 1, j = 0; i < rezline[0]; i++, j++)
		{
			out << numarray1[j] << ' ' << rezline[i] << endl;
		}
		out << "--------Quad--------" << endl;
		rezline = cubicinterpol(numarray, numarray1, n, n1);
		out << rezline[0] - 1 << endl;
		for (int i = 1, j = 0; i < rezline[0]; i++, j++)
		{
			out << numarray1[j] << ' ' << rezline[i] << endl;
		}
		out << "--------Cubic--------" << endl;
		out.close();
		break;
	}
	default: 
		return 4;
	}
	for (int i = 0; i < n; i++)
		delete[] numarray[i];
	delete[] numarray;
	delete[] numarray1;
	delete[] rezline;
	return 10;
}