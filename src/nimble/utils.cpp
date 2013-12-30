#include "utils.h"

#include <cstdlib>
#include <cmath>
#include <ctime>

#include "macros.h"

const Vec &Utils::unitVector(float angle)
{
	static Vec tmpVec;
	tmpVec.set(cosf(angle), sinf(angle));
	return tmpVec;
}

const Vec &Utils::angleVector(float angle, float length)
{
	static Vec tmpVec;
	tmpVec.set(cosf(angle) * length, sinf(angle) * length);
	return tmpVec;
}

void Utils::initRandom()
{
	srandom(time(NULL));
}
