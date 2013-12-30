#ifndef BOUNDINGPOLYGONS_H
#define BOUNDINGPOLYGONS_H

#include <string>

#include "boundingshape.h"
#include "polygons/polygongroup.h"
#include "logger.h"

class BoundingPolygons : public BoundingShape
{
	private:
		BoundingPolygons(PolygonGroup *pGroup, const std::string &name);
		friend class BoundingShapeManager;

	private:
		PolygonGroup *m_pGroup;

	public:

		inline void addPolygon(Polygon *pPolygon)
		{
			m_pGroup->addPolygon(pPolygon);
			m_bbox.assign(m_pGroup->boundingBox());
			ASSERT(m_pGroup->areAllConvex(), "Polygons should be all convex.");
		}

		bool intersects(Transformation &thisTrans, const BoundingShape *pShape, Transformation &otherTrans) const;

		inline PolygonGroup *group() const { return m_pGroup; }

		~BoundingPolygons();
};

#endif // BOUNDINGPOLYGONS_H
