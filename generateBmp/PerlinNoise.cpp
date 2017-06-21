#include "PerlinNoise.h"
# include <cstdint>
# include <numeric>
# include <algorithm>

double fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double lerp(double t, double a, double b)
{
	return a + t * (b - a);
}

void PerlinNoise::SetSeed(float seed)
{
	m_seed = seed;
}

void PerlinNoise::Setfxfy(float fx, float fy)
{
	m_fx = fx;
	m_fy = fy;
}

void PerlinNoise::SetOctaves(float octaves)
{
	m_octaves = octaves;
}

int PerlinNoise::noise(int posx, int posy) {
	return noise(posx, posy, 0);
}
int PerlinNoise::octaveNoise(int x, int y)
{
	int result = 0.0;
	int amp = 1.0;

	for (std::int32_t i = 0; i < m_octaves; ++i)
	{
		result += noise(x, y) * amp;
		x *= 2.0;
		y *= 2.0;
		amp *= 0.5;
	}

	return result;
}
int PerlinNoise::noise(int posx, int posy, int posz)
{
	float x = posx / m_fx;
	float y = posy / m_fy;
	float z =  posz;


	x -= std::floor(x);
	y -= std::floor(y);
	z -= std::floor(z);

	const double u = fade(x);
	const double v = fade(y);
	const double w = fade(z);

	return lerp(
		w, 
		lerp(
			v, 
			lerp(
				u, 
				Random(),
				Random()
			),
			lerp(
				u, 
				Random(),
				Random()
			)
		),
		lerp(
			v, 
			lerp(
				u, 
				Random(),
				Random()
			),
			lerp(
				u, 
				Random(),
				Random())
			)
		);
}

PerlinNoise::PerlinNoise()
{
}

PerlinNoise::~PerlinNoise()
{
}
