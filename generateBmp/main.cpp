#include <functional>
#include <iostream>
#include <fstream>
#include "PerlinNoise.h"
#include "functionsRandom.h"

float red(int x)
{
	return 0x0000FFFF;
}

//
//float* GenerateWhiteNoise(int width, int height)
//{
//	float* baseNoise = new float[width * height];
//
//	for (int y = 0; y < height; y++) {
//		for (int x = 0; x < width; x++) {
//			baseNoise[y*width + x] = floatRandom();
//		}
//	}return baseNoise;
//}

//float* GenerateSmoothNoise(float* baseNoise, int octave, int width, int height)
//{
//
//	float* smoothNoise = new float[width * height];
//
//	int samplePeriod = 1 << octave; // calculates 2 ^ k
//	float sampleFrequency = 1.0f / samplePeriod;
//
//	for (int i = 0; i < width; i++)
//	{
//		//calculate the horizontal sampling indices
//		int sample_i0 = (i / samplePeriod) * samplePeriod;
//		int sample_i1 = (sample_i0 + samplePeriod) % width; //wrap around
//		float horizontal_blend = (i - sample_i0) * sampleFrequency;
//
//		for (int j = 0; j < height; j++)
//		{
//			//calculate the vertical sampling indices
//			int sample_j0 = (j / samplePeriod) * samplePeriod;
//			int sample_j1 = (sample_j0 + samplePeriod) % height; //wrap around
//			float vertical_blend = (j - sample_j0) * sampleFrequency;
//
//			//blend the top two corners
//			
//			float top = Interpolate(baseNoise[sample_j0*width + sample_i0],
//				baseNoise[sample_j0*width + sample_i1], horizontal_blend);
//
//			//blend the bottom two corners
//			float bottom = Interpolate(baseNoise[sample_j1*width + sample_i0],
//				baseNoise[sample_j1*width + sample_i1], horizontal_blend);
//
//			//final blend
//			smoothNoise[j*width + i] = Interpolate(top, bottom, vertical_blend);
//		}
//	}
//	return smoothNoise;
//}

//float* GeneratePerlinNoise(float* baseNoise, int width, int height, int octaveCount)
//{
//
//	 //an array of 2D arrays containing
//	float *smoothNoiseTemp;
//	float *perlinNoise = new float[width * height];
//	for (int i = 0; i < width*height; i++)
//	{
//		perlinNoise[i] = 0;
//	}
//	float persistance = .5f;
//	float amplitude = 1.0f;
//	float totalAmplitude = 0.0f;
//	//generate smooth noise
//	for (int i = 0; i < octaveCount; i++)
//	{
//		smoothNoiseTemp = GenerateSmoothNoise( baseNoise, octaveCount - i, width,  height);
//		amplitude *= persistance;
//		totalAmplitude += amplitude;
//		for (int i = 0; i < width*height; i++)
//		{
//			perlinNoise[i] += smoothNoiseTemp[i] * amplitude;
//		}
//		delete[] smoothNoiseTemp;
//	}
//
//	//normalisation
//	for (int i = 0; i < width*height; i++)
//	{
//		perlinNoise[i] /= totalAmplitude;
//	}
//	return perlinNoise;
//}

void GenerateBMP(float(*callback)(int), int width, int height) {

	int frequency = 1;
	int octaves = 7;
	int seed = 3318026815;
	width = 512;
	height = 512;

	PerlinNoise perlinNoise;
	perlinNoise.SetSize(width, height);
	perlinNoise.SetOctaves(octaves);
	perlinNoise.GeneratePerlinNoise();

	char * buffer = new char[width * height * 4];
	int counter = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char * pointerInt;
			pointerInt = (char*)&buffer[y*width * 4 + x * 4];
			//float value = callback(width*y + x);
			float value = perlinNoise.GetValuePerlinNoise(width*y + x);

			*pointerInt = static_cast<unsigned char>(value *255);
			pointerInt++;
			*pointerInt = static_cast<unsigned char>(value *255);
			pointerInt++;
			*pointerInt = static_cast<unsigned char>(value *255);
			pointerInt++;
			*pointerInt = static_cast<unsigned char>(value *255);

			counter++;
		}
	}

	char* header = new char[54];
	int * pointerInt;

	header[0] = 0x42;
	header[1] = 0x4d;
	pointerInt = (int*)&header[2];
	*pointerInt = (height*width * 4);
	pointerInt = (int*)&header[6];
	*pointerInt = 0;
	pointerInt = (int*)&header[10];
	*pointerInt = 0x00000036;
	pointerInt++;
	*pointerInt = 0x00000028;
	pointerInt++;
	*pointerInt = width;
	pointerInt++;
	*pointerInt = height;
	header[26] = 0x01;
	header[27] = 0x00;
	header[28] = 0x20;
	header[29] = 0x00;
	pointerInt = (int*)&header[30];
	*pointerInt = 0;
	pointerInt++;
	*pointerInt = 0;
	pointerInt++;
	*pointerInt = 0; pointerInt++;
	*pointerInt = 0; pointerInt++;
	*pointerInt = 0; pointerInt++;
	*pointerInt = 0;

	std::ofstream image("image.bmp", std::ios::out | std::ios::binary);
	image.write(header, sizeof(char) * 54);
	image.write(buffer, sizeof(char) * width * height * 4);
	image.close();

}
void main() {

	int frequency = 16;
	int octaves = 2;
	int seed = 3318026815;
	int width = 512;
	int height = 512;

	/*PerlinNoise perlinNoise;
	perlinNoise.SetSize(width, height);
	perlinNoise.SetOctaves(octaves);
	perlinNoise.GeneratePerlinNoise();
*/

	GenerateBMP(red, width, height);
	std::cout << "hola";
}



