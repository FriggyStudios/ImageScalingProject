// File: Matrix09.h (version: Week09)
//   What: Header file for matrix class, including overloading = and *
// Author: Niall Madden
//   Date: 09/03/2017
// Note: Implementation for a square matrix
// Changes from Matrix08.h
//    change #include to include latest header files.
//    Added zero() method

//Date: 30/03/2017
//Author: Kevin McGinley
//Changed N*N matrix to N*M matrix
//Added setNM function

#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

class Matrix {
private:
	char *entries;
	unsigned int N;
	unsigned int M;
public:
	Matrix();
	Matrix(unsigned int N, unsigned int M);
	Matrix(const Matrix &m); // New copy constructor
	~Matrix(void);

	Matrix &operator=(const Matrix &B); // overload assignment operator

	unsigned int sizeN(void) { return (N); };
	unsigned int sizeM(void) { return (M); };
	void setNM(unsigned int N, unsigned int M);
	char getij(unsigned int i, unsigned int j);
	void setij(unsigned int i, unsigned int j, char x);

	void print(void);

	void zero(void); // New for Week 9
};
#endif
