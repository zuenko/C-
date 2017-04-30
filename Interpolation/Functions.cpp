#include <iostream>
#include <cmath>
#include "Header.h"
using namespace std;

void Sort(float* arr, int size)
{
	int i, j;
	float tmp;
	for (i = 0; i < size - 1; ++i) // i - номер прохода
	{
		for (j = 0; j < size - 1; ++j) // внутренний цикл прохода
		{
			if (arr[j + 1] < arr[j])
			{
				tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void Sort(float** arr, int size)
{
	int i, j;
	float tmp, tmp2;
	for (i = 0; i < size - 1; ++i) // i - номер прохода
	{
		for (j = 0; j < size - 1; ++j) // внутренний цикл прохода
		{
			if (arr[j + 1][0] < arr[j][0])
			{
				tmp2 = arr[j + 1][1];
				tmp = arr[j + 1][0];
				arr[j + 1][1] = arr[j][1];
				arr[j + 1][0] = arr[j][0];
				arr[j][0] = tmp;
				arr[j][1] = tmp;
			}
		}
	}
}

float * gauss(float **a, float *y, int n)
{
	float *x, max;
	int k, index;
	const double eps = 0.00001;
	x = new float[n];
	k = 0;
	while (k < n)
	{
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		if (max < eps)
		{
			delete[]x;
			return NULL;
		}
		for (int j = 0; j < n; j++)
		{
			float temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		float temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		for (int i = k; i < n; i++)
		{
			float temp = a[i][k];
			if (abs(temp) < eps) continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k) continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}

float * lineinterpol(float **numarray, float * numarray1, int n, int n1)
{
	float * mass = new float[n1];
	int h = 1, g = 0;
	for (int i = 0; i<n - 1; i++)
	{
		{
			if (numarray[i][0]<numarray1[g] && numarray1[g]<numarray[i + 1][0])
			{
				mass[h] = numarray[i][1] - (numarray[i][1] - numarray[i + 1][1])*(numarray1[g] - numarray[i][0]) / (numarray[i + 1][0] - numarray[i][0]);
				//f(X1)-( f(X1) - f(X3) )*(X - X1)/(X2 - X1)
				h++; g++;
			}
			else { g++; i--; }
		}
	}
	mass[0] = h;
	return mass;
}

float * quadinterpol(float **numarray, float * numarray1, int n, int n1)
{
	float * mass = new float[n1];
	int h = 1, g = 0;
	for (int i = 1; i<n - 1; i++)
	{
		{
			if (numarray[i - 1][0]<numarray[i][0] && numarray[i][0]<numarray[i + 1][0] && numarray[i - 1][0]<numarray1[g] && numarray1[g]<numarray[i + 1][0])
			{
				mass[h] =
					numarray[i - 1][1] * (((numarray1[g] - numarray[i][0])*(numarray1[g] - numarray[i + 1][0])) / ((numarray[i - 1][0] - numarray[i][0])*(numarray[i - 1][0] - numarray[i + 1][0]))) +
					numarray[i][1] * (((numarray1[g] - numarray[i - 1][0])*(numarray1[g] - numarray[i + 1][0])) / ((numarray[i][0] - numarray[i - 1][0])*(numarray[i][0] - numarray[i + 1][0]))) +
					numarray[i + 1][1] * (((numarray1[g] - numarray[i - 1][0])*(numarray1[g] - numarray[i][0])) / ((numarray[i + 1][0] - numarray[i - 1][0])*(numarray[i + 1][0] - numarray[i][0])));

				//f(x1)*(((x-x2)*(x-x3))/((x1-x2)*(x1-x3)))+f(x2)*(((x-x1)*(x-x3))/((x2-x1)*(x2-x3)))+f(x3)*(((x-x1)*(x-x2))/((x3-x1)*(x3-x2)))
				h++; g++;
			}
			else { g++; i--; }
		}
	}
	mass[0] = h;
	return mass;
}

float * cubicinterpol(float **numarray, float * numarray1, int n, int n1)
{
	int g = 0, h = 1;
	float **a = new float*[4];
	float *y = new float[4];
	float *mass = new float[n1];
	float *prom;
	for (int i = 0; i < 4; i++)
	{
		a[i] = new float[4];
	}
	for (int j = 0; j < n; j++)
	{
		if (g < 4)
		{
			a[g][0] = pow(numarray[j][0], 3);
			a[g][1] = pow(numarray[j][0], 2);
			a[g][2] = numarray[j][0];
			a[g][3] = 1;
			y[g] = numarray[j][1];
			g++;

		}
		else
		{
			prom = gauss(a, y, 4);
			mass[h] = prom[0] * pow(numarray1[h], 3) + prom[1] * pow(numarray1[h], 2) + prom[2] * numarray1[h] + prom[3];
			g = 0; j = j - 4; h++;
		}
	}
	mass[0] = h;
	for (int i = 0; i < 4; i++)
		delete[]a[i];
	delete[]a;
	delete[]y;
	return mass;
}
