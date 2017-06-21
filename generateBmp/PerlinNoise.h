#pragma once
#include <functional>


class PerlinNoise
{
public:
	float m_seed;
	float m_octaves;
	float m_fx;
	float m_fy;

	void SetSeed(float seed);
	void Setfxfy(float fx, float fy);
	void SetOctaves(float octaves);

	int noise(int x, int y);
	int octaveNoise(int x, int y);

	int noise(int x, int y, int z);
	std::function<int()> Random;
	PerlinNoise();
	~PerlinNoise();

private:

};