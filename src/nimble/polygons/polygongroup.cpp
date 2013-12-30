#include "polygongroup.h"

#include "../logger.h"

PolygonGroup::PolygonGroup(const PolygonGroup &group)
	: m_bbox(group.m_bbox)
{
	for(ConstPolygonPIterator it = group.m_polys.begin();
		it != group.m_polys.end(); ++it)
	{
		m_polys.push_back(new Polygon(**it));
	}
}

PolygonGroup::PolygonGroup(Polygon *pPolygon)
	: m_bbox(pPolygon->boundingBox())
{
	m_polys.push_back(pPolygon);
}

PolygonGroup::PolygonGroup()
{

}

PolygonGroup::~PolygonGroup()
{
	freeAll();
}

void PolygonGroup::freeAll()
{
	for(PolygonPIterator it = m_polys.begin();
		it != m_polys.end(); ++it)
	{
		delete *it;
	}

	m_polys.clear();
}

void PolygonGroup::updateBoundingBox()
{
	if(m_polys.size() == 0)
		return;

	m_bbox.assign(m_polys.front()->boundingBox());

	for(PolygonPIterator it = m_polys.begin();
		it != m_polys.end(); ++it)
	{
		extendBBox(*it);
	}
}

bool PolygonGroup::areAllConvex()
{
	for(PolygonPIterator it = m_polys.begin();
		it != m_polys.end(); ++it)
	{
		if(!(*it)->isConvex())
			return false;
	}

	return true;
}

void PolygonGroup::minimize()
{
	std::vector<Polygon*> tmpPolys;
	bool found;


	do
	{
		found = false;

		while(m_polys.size() != 0)
		{
			bool glued = false;

			PolygonPIterator pi = m_polys.begin() + 1;
			Polygon *pTmpPoly = new Polygon(*(m_polys.front()));

			while(pi != m_polys.end())
			{
				if(pTmpPoly->glueCommonEdge(**pi))
				{
					if(pTmpPoly->isConvex())
					{
						delete m_polys.front();
						delete *pi;
						m_polys.erase(pi);
						found = true;
						glued = true;

						tmpPolys.push_back(pTmpPoly);

						pTmpPoly = 0;
						break;
					}

					delete pTmpPoly;
					pTmpPoly = new Polygon(*(m_polys.front()));
				}

				++pi;
			}

			if(!glued)
			{
				delete pTmpPoly;
				tmpPolys.push_back(m_polys.front());
			}

			m_polys.erase(m_polys.begin());
		}

		m_polys.assign(tmpPolys.begin(), tmpPolys.end());
		tmpPolys.clear();

	} while(found);
}


bool PolygonGroup::intersects(Transformation &thisTrans, const PolygonGroup &group, Transformation &otherTrans)
{

	ConstPolygonPIterator pA;
	ConstPolygonPIterator pB;
	Rect bboxA;
	Rect bboxB;

	bool collides = false;

	pA = m_polys.begin();

	while(pA != m_polys.end())
	{
		pB = group.m_polys.begin();

		while(pB != group.m_polys.end())
		{
			Polygon *polyA = *pA;
			Polygon *polyB = *pB;

			bboxA.assign(polyA->boundingBox());
			bboxB.assign(polyB->boundingBox());

			bboxA.transform(thisTrans);
			bboxB.transform(otherTrans);

			if(bboxA.notIntersects(bboxB))
			{
				++pB;
				continue;
			}

			if(thisTrans.transformed())
			{
				polyA = new Polygon(*polyA);
				polyA->transformLinear(thisTrans);
			}

			if(otherTrans.transformed())
			{
				polyB = new Polygon(*polyB);
				polyB->transformLinear(otherTrans);
			}

			if(polyA->intersects(thisTrans, *polyB, otherTrans))
			{
				collides = true;
			}

			if(polyA != *pA)
				delete polyA;

			if(polyB != *pB)
				delete polyB;

			++pB;
		}

		++pA;
	}


	return collides;
}
