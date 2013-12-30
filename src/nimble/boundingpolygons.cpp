#include "boundingpolygons.h"
#include "logger.h"

BoundingPolygons::BoundingPolygons(PolygonGroup *pGroup, const std::string &name)
	: BoundingShape(BoundingShape::T_POLYGON, name)
{
	m_pGroup = pGroup;
	m_bbox.assign(m_pGroup->boundingBox());

	ASSERT(m_pGroup->areAllConvex(), "Polygons should be all convex.");
}

BoundingPolygons::~BoundingPolygons()
{
	if(m_pGroup != 0)
		delete m_pGroup;
}


bool BoundingPolygons::intersects(Transformation &thisTrans, const BoundingShape *pShape, Transformation &otherTrans) const
{
	const BoundingPolygons *pBPolys = 0;

	switch(pShape->type())
	{
		case BoundingShape::T_POLYGON:

			pBPolys = dynamic_cast<const BoundingPolygons*>(pShape);

			if(m_pGroup->intersects(thisTrans, *pBPolys->m_pGroup, otherTrans))
			{
				return true;
			}

		break;

		case BoundingShape::T_CIRCLE:

		break;

		default:
			ERROR("Shouldn't be here!");
	}

	return false;
}
