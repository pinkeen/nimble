#include "tesselator.h"

#include "../logger.h"
#include <cmath>

#define TRI_AREA(a, b, c) (fabsf((a.x() - c.x()) * (b.y() - c.y())) - ((b.x() - c.x()) * (a.y() - c.y())))

Tesselator::Tesselator()
{
}

bool Tesselator::isVertexReflex(const Vec &a, const Vec &b, const Vec &c)
{
	Vec v1(a);
	Vec v2(c);
	v1.sub(b);
	v2.sub(b);

	return v2.cross(v1) <= 0.0f ? true : false;
}

bool Tesselator::isPointInTriangle(const Vec &p, const Vec &a, const Vec &b, const Vec &c)
{
	Vec v0(c);
	Vec v1(b);
	Vec v2(p);

	v0.sub(a);
	v1.sub(a);
	v2.sub(a);

	float dot00 = v0.dot(v0);
	float dot01 = v0.dot(v1);
	float dot02 = v0.dot(v2);
	float dot11 = v1.dot(v1);
	float dot12 = v1.dot(v2);

	float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (u > 0.0f) && (v > 0.0f) && ((u + v) < 1.0f);
}

PolygonGroup *Tesselator::tesselatePolygon(const Polygon *pPolygon)
{

	ASSERT(pPolygon->vertexCount() > 2, "This is not a polygon!");

	PolygonGroup *pGroup = new PolygonGroup();

	const std::vector<Vec> &vertices = pPolygon->vertices();
	std::vector<int> poly;

	for(unsigned int i = 0; i < vertices.size(); ++i)
		poly.push_back(i);

	while(poly.size() > 2)
	{
		//INFO("-->%u", poly.size());
		for(unsigned int i = 0; i < poly.size(); ++i)
		{
		//	INFO("%u", i);
			unsigned int i1 = i;
			unsigned int i2 = (i + 1) % poly.size();
			unsigned int i3 = (i + 2) % poly.size();

			const Vec &v1 = vertices.at(poly.at(i1));
			const Vec &v2 = vertices.at(poly.at(i2));
			const Vec &v3 = vertices.at(poly.at(i3));

		//	INFO("\na %f %f", v1.x(), v1.y());
		//	INFO("b %f %f", v2.x(), v2.y());
		//	INFO("c %f %f", v3.x(), v3.y());

			if(isVertexReflex(v1, v2, v3))
				continue;

		//	INFO("isnt reflex");

			bool ear = true;

			for(unsigned int j = 0; j < poly.size(); ++j)
			{
				if(j != i1 && j != i2 && j != i3)
				{
					if(isPointInTriangle(vertices.at(poly.at(j)), v1, v2, v3))
					{
						ear = false;
						break;
					}
				}
			}

			if(ear)
			{
				Polygon *pPoly = new Polygon();

				pPoly->addVertex(v1);
				pPoly->addVertex(v2);
				pPoly->addVertex(v3);

				pGroup->addPolygon(pPoly);

				poly.erase(poly.begin() + i2);

				break;
			}
		}
	}



	return pGroup;
}
