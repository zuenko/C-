#ifndef TARRAY_H
#define ARRAY_SIZE 1
#define TARRAY_H
#include <iostream>
using namespace std;

class TArray
{
private:
	void ArraySet(float*);
	float *m;//array
	int n; //Length
	float sum;
public:
	int Length(void) const { return n; }
	TArray();
	TArray(int);
	TArray(float*, int);
	TArray(const TArray&);
	void SetItem(float, int);
	void Sort();
	void SizeSet(int);
	void AddItem(float);
	float GetItem(int );
	void AddArray(float*, int);
	void SetArray(float*);
	void PrintArray();
	void Clear();
	float GetItem(int) const;
	float Sum();
	const TArray operator+(const TArray &rv) const;
	const TArray operator+(const float &rv) ;
	const TArray operator=(const TArray &rv);
		const TArray operator[](int i);
	friend ostream& operator<<(ostream&, const TArray&);
	friend istream& operator >> (istream &in, TArray &rv);
	~TArray();
};
#endif 