//Name: Kevin McGinley
//ID: 14372681
//Takes pbm input
//Loads pbm into matrix form
//Takes zoom factor
//Zooms matrix by factor and writes to pbm

#include "Matrix09.h"
#include "PBM.h"
#include <iostream>
#include <sstream>

int main(void)
{
	//pbm input
	std::string fileName;
	std::cout << "Enter file name: ";
	std::cin >> fileName;
	PBM image = PBM(fileName);
	std::cout << "\nLoaded pbm\n";
	//factor input
	std::string factor;
	bool askedFactor = false;
	do
	{
		if (askedFactor)
		{
			std::cout << "Invalid input\n";
		}
		std::cout << "Enter zoom factor: ";
		std::cin >> factor;
		askedFactor = true;
	}while (factor.find_first_not_of("1234567890.-") != std::string::npos);
	std::cout << "Input accepted";
	//transform by factor
	image.TransformZoom(atof(factor.c_str()));
	//output to pbm file
	std::ostringstream output;
	output << "fileNameX" << factor << ".pbm";
	image.WriteMatrixToPBM(output.str());
	std::cout << "\nImage transformed and written to " << output.str() <<'\n';
	return (0);
}
