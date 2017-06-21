#include <functional>
#include <iostream>
#include <fstream>
#include "PerlinNoise.h"
#include "functionsRandom.h"
int red(int x, int y)
{
	return 0x0000FFFF;
}

void GenerateBMP(std::function<int(int, int)> Callback, int width, int height) {

	int frequency = 1;
	int octaves = 2;
	int seed = 3318026815;
	width = 512;
	height = 512;


	PerlinNoise perlinNoise;
	perlinNoise.SetSeed(seed);
	perlinNoise.Setfxfy(width / frequency, height / frequency);
	perlinNoise.SetOctaves(octaves);
	perlinNoise.Random = BasicRandom;

	char * buffer = new char[width * height * 4];
	int counter = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char * pointerInt;
			pointerInt = (char*)&buffer[y*width*4 + x*4];
			float lu = perlinNoise.octaveNoise(x, y);
			*pointerInt =	static_cast<unsigned char>(lu);
			pointerInt++;
			*pointerInt = static_cast<unsigned char>(lu);
			pointerInt++;
			*pointerInt = static_cast<unsigned char>(lu);
			pointerInt++;
			*pointerInt = static_cast<unsigned char>(lu);

			//*pointerInt = perlinNoise.noise(x, y);
			counter++;
		}
	}

	char* header = new char[54];
	int * pointerInt;

	header[0] = 0x42;
	header[1] = 0x4d;
	pointerInt = (int*)&header[2];
	*pointerInt = (height*width*4);
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


	PerlinNoise perlinNoise;
	perlinNoise.SetSeed(seed);
	perlinNoise.Setfxfy(width / frequency, height / frequency);
	perlinNoise.Random = BasicRandom;
	GenerateBMP(red, width, height);
	std::cout << "hola";
}



