#ifndef TESSELATOR_H
#define TESSELATOR_H

#include "../vector.h"
#include "polygon.h"
#include "polygongroup.h"

#include <vector>
#include <list>

class Tesselator
{
	private:

	public:
		static bool isPointInTriangle(const Vec &p, const Vec &a, const Vec &b, const Vec &c);
		static bool isVertexReflex(const Vec &a, const Vec &b, const Vec &c);

		Tesselator();

		PolygonGroup *tesselatePolygon(const Polygon *pPolygon);


};

#endif // TESSELATOR_H
