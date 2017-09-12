#include "PBM.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

//PBM filen name constructor
PBM::PBM(std::string fileName)
	:
	image()
{
	std::ifstream InFile;
	InFile.open(fileName.c_str());

	while (InFile.fail())
	{
		//In case File cannot be opened
		std::cout << "Cannot open " << fileName << " for reading." << std::endl;
		std::cout << "Enter another file name : ";
		std::cin >> fileName;
		InFile.open(fileName.c_str());
	}
	std::cout << "Successfully opened " << fileName << std::endl;

	std::string line;
	// Read the "P1" at the start of the file
	InFile >> line;
	// Read the number of columns and rows
	unsigned int rows, cols;
	InFile >> cols >> rows;
	image.setNM(rows, cols);

	std::cout << "read: cols=" << cols << ", rows=" << rows << std::endl;
	for (unsigned int i = 0; i<rows; i++)
	{
		for (unsigned int j = 0; j<cols; j++)
		{
			char pixel;
			do
			{
				InFile.get(pixel);
			} while (pixel == ' ' || pixel == '\n');
			image.setij(i, j, (pixel));
		}
	}
	InFile.close();
}
//Matrix object constructor
PBM::PBM(Matrix image)
	:
	image()
{
	this->image = image;
}

PBM::~PBM()
{
}

//Scale image by factor > 0
void PBM::TransformZoom(float factor)
{
	if (factor >= 1)
	{
		TransformZoomIn(factor);
	}
	else
	{
		//Convert factor < 1 to its inverse
		float newFactor = pow(factor, -1);
		if (floor(newFactor) != newFactor)
		{
			TransformZoomOut(newFactor);
		}
		else
		{
			TransformZoomOut(int(newFactor));
		}
	}
}

//Scale up image by factor > 1 
//Map pixel to be transformed to original matrix
//Take values from original matrix to decided transformed pixel
void PBM::TransformZoomIn(float factor)
{
	//New transformed matrix
	Matrix transformMatrix((unsigned int)(factor*image.sizeN()), (unsigned int)(factor*image.sizeM()));

	for (unsigned int i = 0; i < transformMatrix.sizeN(); i++)
	{
		for (unsigned int j = 0; j < transformMatrix.sizeM(); j++)
		{
			//Pixel location of original matrix
			unsigned int left, right, top, bottom;
			left = unsigned int(floor((int)((j) / factor)));
			right = unsigned int(ceil((int)((j) / factor)));
			top = unsigned int(ceil((int)((i) / factor)));
			bottom = unsigned int(floor((int)((i) / factor)));

			//Mapped to transformed matrix
			unsigned int newPixel = (unsigned int)((image.getij(top, left) + image.getij(bottom, left) +
				image.getij(top, right) + image.getij(bottom, right))/((double)4));
			transformMatrix.setij(i, j, newPixel);
		}
	}
	image = transformMatrix;
}

//Scale down image by float factor > 1
//Not accurate for some odd integer factors
//Find cols and rows to keep
//Discard unwanted rows first
//Then discard unwanted cols	
void PBM::TransformZoomOut(float factor)
{
	//Rows and cols to keep
	int *Is;
	int *Js;
	Is = new int[image.sizeN()];
	Js = new int[image.sizeM()];
	//Number of Rows and cols
	unsigned int iIndex = 0;
	unsigned int jIndex = 0;
	//localFactor to be incremented by factor
	float localFactor = factor;
	//Range close to localFactor for row and col to be kept
	float plusORMinus = (factor - 1) / 2.f;
	
	for (unsigned int i = 1; i < image.sizeN(); i++)
	{
		//Increment localFactor if index too large
		if ((float)i > localFactor + plusORMinus)
		{
			localFactor += factor;
		}		
		//If row in range, discard row, else add to Is
		if(localFactor > (float)i- plusORMinus && localFactor < (float)i+ plusORMinus)
		{
			//discard
		}
		else
		{
			Is[iIndex++] = i;
		}
	}
	//Reset localFactor
	localFactor = factor;
	for (unsigned int i = 1; i < image.sizeM(); i++)
	{
		//Increment localFactor if index too large
		if ((float)i > localFactor + factor - plusORMinus)
		{
			localFactor += factor;
		}
		//If col in range, discard row, else add to Js
		if (localFactor >(float)i - plusORMinus && localFactor < (float)i + plusORMinus)
		{
			//discard
		}
		else
		{
			Js[jIndex++] = i;
		}
	}
	//Discard unwanted rows
	Matrix transformMatrixRowDeleted(iIndex, image.sizeM());
	unsigned int localI = 0;
	for (unsigned int i = 0; i < image.sizeN(); i++)
	{
		for (unsigned int j = 0; j < image.sizeM(); j++)
		{
			if (Is[localI] != i)
			{
				break;
			}
			transformMatrixRowDeleted.setij(localI, j, image.getij(i, j));
		}
		if (Is[localI] == i)
		{
			localI++;
		}
	}
	//Discard unwanted cols
	Matrix transformMatrixColRowDeleted(iIndex, jIndex);
	unsigned int localJ = 0;

	for (unsigned int j = 0; j < transformMatrixRowDeleted.sizeM(); j++)
	{
		for (unsigned int i = 0; i <iIndex; i++)
		{
			if (Js[localJ] != j)
			{
				break;
			}
			transformMatrixColRowDeleted.setij(i, localJ, transformMatrixRowDeleted.getij(i, j));
		}
		if (Js[localJ] == j)
		{
			localJ++;
		}
	}
	image = transformMatrixColRowDeleted;

	//Clean up
	delete Is;
	delete Js;
}

//Scale down image by int factor > 1
void PBM::TransformZoomOut(int factor)
{
	//Rows and cols to keep
	int *Is;
	int *Js;
	Is = new int[image.sizeN()];
	Js = new int[image.sizeM()];
	//Number of Rows and cols
	unsigned int iIndex = 0;
	unsigned int jIndex = 0;

	//Find wanted rows
	for (unsigned int i = 1; i < image.sizeN(); i++)
	{
		if (i%factor == 0)
		{
			Is[iIndex++] = i;
		}
	}
	//Find wanted cols
	for (unsigned int i = 1; i < image.sizeM(); i++)
	{
		if (i%factor == 0)
		{
			Is[jIndex++] = i;
		}
	}
	//Discared unwanted rows
	Matrix transformMatrixRowDeleted(iIndex, image.sizeM());
	unsigned int localI = 0;
	for (unsigned int i = 0; i < image.sizeN(); i++)
	{
		for (unsigned int j = 0; j < image.sizeM(); j++)
		{
			if (Is[localI] != i)
			{
				break;
			}
			transformMatrixRowDeleted.setij(localI, j, image.getij(i, j));
		}
		if (Is[localI] == i)
		{
			localI++;
		}
	}
	//Discared unwanted cols
	Matrix transformMatrixColRowDeleted(iIndex, jIndex);
	unsigned int localJ = 0;

	for (unsigned int j = 0; j < transformMatrixRowDeleted.sizeM(); j++)
	{
		for (unsigned int i = 0; i <iIndex; i++)
		{
			if (Js[localJ] != j)
			{
				break;
			}
			transformMatrixColRowDeleted.setij(i, localJ, transformMatrixRowDeleted.getij(i, j));
		}
		if (Js[localJ] == j)
		{
			localJ++;
		}
	}
	image = transformMatrixColRowDeleted;
	//Clean up
	delete Is;
	delete Js;
}

//Write Matrix to PBM file
void PBM::WriteMatrixToPBM(std::string fileName)
{
	std::ofstream OutFile;

	OutFile.open(fileName.c_str());
	OutFile << "P1" << std::endl;
	OutFile << image.sizeM() << " " << image.sizeN() << std::endl;

	//Write each entry in image to pbm file
	for (unsigned int i = 0; i<image.sizeN(); i++)
	{
		for (unsigned int j = 0; j<image.sizeM(); j++)
		{
			OutFile << image.getij(i, j);
		}
		OutFile << std::endl;
	}
	OutFile.close();

}
