//Read in PBM files and converts to Matrix
//Transform matrix by floating point positive scalers
//Write matrix to PBM file

#ifndef _PBM_H_INCLUDED
#define _PBM_H_INCLUDED
#include "Matrix09.h"
#include <string>

class PBM
{
private:
	Matrix image;
	void TransformZoomIn(float factor);
	void TransformZoomOut(float factor);
	void TransformZoomOut(int factor);
public:
	PBM(std::string fileName);
	PBM(Matrix image);
	~PBM();
	void TransformZoom(float factor);
	void WriteMatrixToPBM(std::string fileName);
	Matrix GetMatrix() { return image; };
};

#endif