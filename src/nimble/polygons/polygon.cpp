#include "polygon.h"

#include "../macros.h"
#include "../logger.h"
#include "tesselator.h"

Polygon::Polygon()
{
}

Polygon::Polygon(const Rect &rect)
{
	m_verts.push_back(rect.topLeft());
	m_verts.push_back(Vec(rect.bottomRight().x(), rect.topLeft().y()));
	m_verts.push_back(rect.bottomRight());
	m_verts.push_back(Vec(rect.topLeft().x(), rect.bottomRight().y()));

	m_bbox.assign(rect);
}

Polygon::Polygon(const Polygon &polygon)
	: m_bbox(polygon.m_bbox)
{
	m_verts.assign(polygon.m_verts.begin(), polygon.m_verts.end());
}

bool Polygon::isConvex()
{
	ASSERT(m_verts.size() > 2, "This is not a polygon!");

	VertIterator i1 = m_verts.end() - 2;
	VertIterator i2 = m_verts.end() - 1;
	VertIterator i3 = m_verts.begin();

	while(i3 != m_verts.end())
	{
		if(Tesselator::isVertexReflex(*i1, *i2, *i3))
			return false;
		i1 = i2;
		i2 = i3;
		++i3;
	}

	return true;
}

bool Polygon::glueCommonEdge(const Polygon &polygon)
{
	ASSERT(m_verts.size() > 2, "This is not a polygon!");
	ASSERT(polygon.vertexCount() > 2, "This is not a polygon!");

	VertIterator ai1 = m_verts.end() - 1;
	VertIterator ai2 = m_verts.begin();

	ConstVertIterator bi1;
	ConstVertIterator bi2;

	bool found = false;

	while(ai2 != m_verts.end())
	{
		bi1 = polygon.m_verts.end() - 1;
		bi2 = polygon.m_verts.begin();

		while(bi2 != polygon.m_verts.end())
		{
			if(ai1->equals(*bi2) && ai2->equals(*bi1))
			{
				found = true;
				break;
			}

			bi1 = bi2;
			++bi2;
		}

		if(found)
			break;

		ai1 = ai2;
		++ai2;
	}

	if(!found)
		return false;

	unsigned int a2pos = ai2 - m_verts.begin();

	++bi2;
	if(bi2 == polygon.m_verts.end())
		bi2 = polygon.m_verts.begin();

	while(bi2 != bi1)
	{
		m_verts.insert(m_verts.begin() + a2pos, *bi2);
		extendBBox(*bi2);

		++a2pos;

		++bi2;
		if(bi2 == polygon.m_verts.end())
			bi2 = polygon.m_verts.begin();
	}

	return true;
}

void Polygon::projectionAxis(Vec &axis, const Vec &edgeA, const Vec &edgeB)
{
	axis.assign(edgeB);
	axis.sub(edgeA);
	axis.perp();
	axis.norm();
}

void Polygon::projectedRange(const Vec &axis, const Vec &position, const Polygon &poly, float &min, float &max)
{
	ConstVertIterator p = poly.m_verts.begin() + 1;

	min = max = poly.m_verts.front().dot(axis);

	while(p != poly.m_verts.end())
	{
		float pos = p->dot(axis);

		if(pos > max)
			max = pos;

		if(pos < min)
			min = pos;

		++p;
	}

	float tmp = position.dot(axis);

	min += tmp;
	max += tmp;
}

void Polygon::transformLinear(Transformation &trans)
{
	VertIterator it = m_verts.begin();

	while(it != m_verts.end())
	{
		trans.transformLinear(*it);
		++it;
	}

	m_bbox.transformLinear(trans);
}

bool Polygon::intersects(Transformation &thisTrans, const Polygon &polygon, Transformation &otherTrans)
{
	ConstVertIterator p1;
	ConstVertIterator p2;
	float minA, maxA, minB, maxB;

	Vec axis;

	//float maxDist = 0.0f;
	//Vec maxDistAxis;

	p1 = m_verts.end() - 1;
	p2 = m_verts.begin();

	while(p2 != m_verts.end())
	{
		projectionAxis(axis, *p1, *p2);
		projectedRange(axis, thisTrans.position(), *this, minA, maxA);
		projectedRange(axis, otherTrans.position(), polygon, minB, maxB);

		if(maxA < minB || minA > maxB)
			return false;

		/*float dist = (minA < maxB) ? maxB - minA : maxA - minB;

		if(dist > maxDist)
		{
			maxDist = dist;
			maxDistAxis.assign(axis);
		}*/

		p1 = p2;
		++p2;
	}

	p1 = polygon.m_verts.end() - 1;
	p2 = polygon.m_verts.begin();

	while(p2 != polygon.m_verts.end())
	{
		projectionAxis(axis, *p1, *p2);
		projectedRange(axis, thisTrans.position(), *this, minA, maxA);
		projectedRange(axis, otherTrans.position(), polygon, minB, maxB);

		if(maxA < minB || minA > maxB)
			return false;

		/*float dist = (minA < maxB) ? maxB - minA : maxA - minB;

		if(dist > maxDist)
		{
			maxDist = dist;
			maxDistAxis.assign(axis);
		}*/

		p1 = p2;
		++p2;
	}


	/*penDist = maxDist;
	penAxis.assign(maxDistAxis);*/

	return true;
}
