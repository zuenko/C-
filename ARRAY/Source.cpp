#include <iostream>
#include <cmath>
#include "TArray.h"
using namespace std;
TArray::TArray(float*ar, int nlate)
{

	ArraySet(ar);
}
TArray::TArray()
{
	n = ARRAY_SIZE;
	ArraySet(NULL);
}
TArray::TArray(int n)
{
	SizeSet(n);
	ArraySet(NULL);
}
TArray::TArray(const TArray &original)
{
	TArray::n = original.n;
	ArraySet(original.m);
}
void TArray::SetArray(float *ar)
{
	for (int i = 0; ar[i] != '\0'; i++) n++;
	ArraySet(ar);
}
void TArray::SetItem(float item, int index)
{
	m[index] = item;
}
void TArray::AddArray(float *mlate, int nlate)
{

	float *a = new float[n + nlate];
	for (int i = 0; i < n; i++) a[i] = m[i];
	delete[]m;
	m = a;
	n += nlate;
	for (int i = n; i < nlate; i++) m[i] = mlate[i - nlate];
}
void TArray::ArraySet(float *m)
{
	TArray::m = new float[n];
	if (!m) throw 15002;
	if (m == NULL)     for (int i = 0; i < n; i++) TArray::m[i] = 0;
	else for (int i = 0; i < n; i++) TArray::m[i] = m[i];
}
float TArray::GetItem(int i) const
{
	if ((0 <= i) && (i <= n)) return m[i];
	else return 0;
}
void TArray::AddItem(float late)
{

	float *a = new float[n + 1];
	for (int i = 0; i < n; i++) a[i] = m[i];
	delete[]m;
	a[n] = late;
	m = a;
	n = n + 1;
}
float TArray::GetItem(int i)
{
	if (0 <= i&&i < n) return m[i];
	else throw 11009;
}
float TArray::Sum()
{
	sum = 0;
	for (int i = 0; i < n; i++) {
		sum += m[i];
	}
	return sum;
}
void TArray::Sort()
{
	int i, j;
	float tmp;
	for (i = 1; i<n; i++) {
		j = i;
		while (j>0 && m[j] < m[j - 1]) {
			tmp = m[j];
			m[j] = m[j - 1];
			m[j - 1] = tmp;
			j = j - 1;
		}
	}
}
void TArray::PrintArray()
{
	for (int i = 0; i<n; i++) cout << m[i] << " ";
}
TArray::~TArray()
{
	delete[]m;
}
const TArray TArray::operator+(const TArray &rv) const
{

	float *a = new float[n + rv.n];
	for (int i = 0; i < n; i++) a[i] = m[i];
	for (int i = n; i < rv.n; i++) a[i] = rv.m[i - rv.n];
	TArray ar1;
	ar1.SetArray(a);
	delete[]a;
	return ar1;
}
ostream& operator<<(ostream &out, const TArray &rv)
{
	for (int i = 0; i < rv.Length(); i++) out << rv.GetItem(i) << " ";
	return out;
}
const TArray TArray::operator=(const TArray &rv)
{
	delete[]m;
	n = rv.n;
	m = new float[n];
	for (int i = 0; i<n; i++) m[i] = rv.m[i];
	return *this;
}
istream& operator >> (istream &in, TArray &rv)
{
	for (int i = 0; i < rv.Length(); i++) in >> rv.m[i];
	return in;
}
void TArray::Clear()
{
	TArray::n = 0;
	TArray::sum = 0;
	delete[]m;
}
const TArray TArray::operator[](int i)
{
	return m[i];
}
const TArray TArray::operator+(const float &rv) 
{

	float *a = new float[n + 1];
	if (!a) throw 15102;
	for (int i = 0; i < n; i++) a[i] = m[i];
	delete[]m;
	a[n] = rv;
	m = a;
	n = n + 1;
	return *this;
}
void TArray::SizeSet(int n)
{
	if (n < 1) throw 12001;
	TArray::n = n;
}