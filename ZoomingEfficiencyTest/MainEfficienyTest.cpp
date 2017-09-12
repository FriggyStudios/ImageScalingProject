//Tests times of zooming algorithms in PBM for various scale factors
//Outputs average time taken for given scale factor

#include "Matrix09.h"
#include "PBM.h"
#include <iostream>
#include <time.h>

int main(void)
{
	float zoomFactors[] = {1/2.f,1/3.f,1/4.f,1/5.f,1/6.f,1/7.f,1/8.f,1/9.f,1/10.f,1/11.f,1/12.f,1/13.f,1/14.f,1/15.f,
		1/1.1f,1/1.2f,1/1.3f,1/1.4f,1/1.5f,1/1.6f,1/1.7f,1/1.8f,1/1.9f,1/2.1f,1/2.3f,1/2.5f,1/2.7f,1/2.9f,1/3.1f,1/3.5f,1/3.9f,1/4.1f,1/4.5f,1/4.9f,1/5.4f,
		/*1,2,4,8,16,32,*/3,9,13,19,22};
	PBM originalImage = PBM("TestImageDog.pbm");

	//Test timing for each scale factor
	for (int i = 0; i < sizeof(zoomFactors) / sizeof(float); i++)
	{
		unsigned int count = 0;
		double timeOfTransformation = 0;
		//Tests times until 20 seconds passed for each scale
		do
		{
			PBM transformedImage = originalImage;
			clock_t start = clock();
			transformedImage.TransformZoom(zoomFactors[i]);
			double time = ((double)(clock() - start)) / (double)CLOCKS_PER_SEC;
			timeOfTransformation += time;
			count++;
		} while (timeOfTransformation < 20);
		timeOfTransformation /= (double)count;

		//Output result
		std::cout << "Transformed " << zoomFactors[i] << " Took time: " << timeOfTransformation << "s\n";
	}
	return (0);
}
