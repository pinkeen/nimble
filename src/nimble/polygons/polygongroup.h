#ifndef POLYGONGROUP_H
#define POLYGONGROUP_H

#include "polygon.h"
#include "../transformation.h"

#include <vector>

class PolygonGroup
{
	private:
		std::vector<Polygon*> m_polys;

		typedef std::vector<Polygon*>::iterator PolygonPIterator;
		typedef std::vector<Polygon*>::const_iterator ConstPolygonPIterator;

		Rect m_bbox;

		inline void extendBBox(Polygon *pPoly)
		{
			m_bbox.merge(pPoly->boundingBox());
		}

	public:
		PolygonGroup(Polygon *pPolygon);
		PolygonGroup(const PolygonGroup &group);
		PolygonGroup();
		~PolygonGroup();

		inline void addPolygon(Polygon *pPolygon)
		{
			m_polys.push_back(pPolygon);

			if(m_polys.size() == 1)
			{
				m_bbox.assign(pPolygon->boundingBox());
				return;
			}

			extendBBox(pPolygon);
		}

		inline unsigned int polygonCount() const { return m_polys.size(); }
		inline const Polygon *polygon(unsigned int index) { return m_polys.at(index); }
		inline const Rect &boundingBox() const { return m_bbox; }
		inline const std::vector<Polygon*> &polygons() const { return m_polys; }

		void minimize();
		void freeAll();

		bool areAllConvex();

		void updateBoundingBox();

		bool intersects(Transformation &thisTrans, const PolygonGroup &group, Transformation &otherTrans);
};

#endif // POLYGONGROUP_H
