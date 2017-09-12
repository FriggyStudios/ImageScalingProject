
#include <iostream>
#include "Matrix09.h" 

// Basic constructor. See below for copy constructor
Matrix::Matrix()
{
	this->N = 2;
	this->M = 2;
	entries = new char[N*M];

	//std::cerr << "Created: " << N << "*" << M;
}

Matrix::Matrix (unsigned int N, unsigned int M)
{
  this->N = N;
  this->M = M;
  entries = new char[N*M];
}


Matrix::~Matrix(void)
{
  delete [] entries;
}

void Matrix::setij(unsigned int i, unsigned int j, char x)
{
	if (i < N && j < M)
		entries[i*M + j] = x;
	else
		std::cerr << "Matrix::setij(): Index out of bounds. " << i << ', ' << j << std::endl;
}

char Matrix::getij(unsigned int i, unsigned int j)
{
	if (i < N && j < M)
		return(entries[i*M + j]);
	else
	{
		std::cerr << i << "  " << j << std::endl;
		std::cerr << "Matrix::getij(): Index out of bounds." << std::endl;
		return(0);
	}
}

void Matrix::print (void)
{
//   std::cout << "Matrix is of size " << M << "-by-" << N << std::endl;
  for (unsigned int i=0; i<N; i++)
  {
    for (unsigned int j=0; j<M; j++)
      std::cout << "[" << entries[i*M+j] << "]";
    std::cout << std::endl;
  }
}

////////////////////////////////////////////////
// Everything above this is from Week 7       //
// Everything below this is from Week 8 and 9 //
////////////////////////////////////////////////

// Matrix copy constructor
Matrix::Matrix (const Matrix &m)
{
  N = m.N;
  M = m.M;
  entries = new char[N*M];
  for (unsigned int i=0; i<N*M; i++)
    entries[i] = m.entries[i];
}


// Overload the assignment = operator. 
Matrix &Matrix::operator=(const Matrix &B)
{
  if (this == &B)
    return(*this); // Taking care for self-assignment

  delete [] entries; // Just in case there was any memory
  // already allocated to this
  N = B.N;
  M = B.M;
  entries = new char[(B.N)*(B.M)];
  for (unsigned int i=0; i<N*M; i++)
    entries[i] = B.entries[i];
      
  return(*this);      
}

////////////////////////////////////////////////
// Everything above this is from Week 7 and 8 //
// Everything below this is from Week 9 //
////////////////////////////////////////////////
void Matrix::zero (void)
{
  for (unsigned int i=0; i<N; i++)
    for (unsigned int j=0; j<M; j++)
      entries[i*M+j] = 0;
}

//Reset N, M and entries
void Matrix::setNM(unsigned int N, unsigned int M)
{
	this->N = N;
	this->M = M;
	delete[] entries;
	entries = new char[N*M];

}
