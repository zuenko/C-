#ifndef HEADER_H
#define HEADER_H

float * lineinterpol(float**, float *, int, int);
float * quadinterpol(float**, float *, int, int);
float * cubicinterpol(float**, float *, int, int);
float * gauss(float **, float *, int);
void Sort(float*, int);
void Sort(float**, int);

#endif