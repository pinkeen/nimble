#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cmath>

#include "vector.h"

namespace Utils
{
	inline float randFloat() { return (float)random() / (float)RAND_MAX; }
	inline float randFloat(float to) { return (float)random() / (float)RAND_MAX * to; }
	inline float randFloat(float from, float to) { return (float)random() / (float)RAND_MAX * (to - from) + from; }

	inline int randInt() { return random(); }
	inline int randInt(int to) { return random() % (to + 1); }
	inline int randInt(int from, int to) { return random() % (to - from + 1) + from; }

	inline float degToRad(float angle) { return angle * M_PI / 180.f; }

	const Vec &unitVector(float angle);
	const Vec &angleVector(float angle, float length);

	void initRandom();
}

#endif // UTILS_H
