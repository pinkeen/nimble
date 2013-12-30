#include "boundingshapemanager.h"

#include "logger.h"

#include "polygons/tesselator.h"

BoundingShapeManager::BoundingShapeManager()
{

}

BoundingShapeManager::~BoundingShapeManager()
{
	freeAll();
}

void BoundingShapeManager::freeAll()
{
	ShapePIterator it = m_shapes.begin();

	while(it != m_shapes.end())
	{
		delete it->second;
		++it;
	}

	m_shapes.clear();
}

BoundingShape *BoundingShapeManager::shape(const std::string &name) const
{
	ConstShapePIterator it = m_shapes.find(name);

	ASSERT(it != m_shapes.end(), "Could not find bounding shape '%s'!",
	       name.c_str());

	return it->second;
}


BoundingPolygons *BoundingShapeManager::createBoundingPolygons(const std::string &name, PolygonGroup *pGroup)
{
	BoundingPolygons *pPolys = new BoundingPolygons(pGroup, name);
	m_shapes[name] = pPolys;

	return pPolys;
}

BoundingPolygons *BoundingShapeManager::createBoundingPolygons(const std::string &name, Polygon *pPolygon)
{
	Tesselator t;

	PolygonGroup *pGroup = t.tesselatePolygon(pPolygon);
	pGroup->minimize();

	delete pPolygon;

	BoundingPolygons *pPolys = new BoundingPolygons(pGroup, name);
	m_shapes[name] = pPolys;

	return pPolys;
}

BoundingPolygons *BoundingShapeManager::createBoundingPolygons(const std::string &name, const Rect &rect)
{
	BoundingPolygons *pPolys = new BoundingPolygons(new PolygonGroup(new Polygon(rect)), name);
	m_shapes[name] = pPolys;

	return pPolys;
}

BoundingPolygons *BoundingShapeManager::createBoundingPolygons(const std::string &name, Animation *pAnim, float scale)
{
	Rect rect(pAnim->boundingBox());

	rect.sub(pAnim->boundingBox().center());

	if(scale != 1.0f)
		rect.mult(scale);

	BoundingPolygons *pPolys = new BoundingPolygons(new PolygonGroup(new Polygon(rect)), name);
	m_shapes[name] = pPolys;

	return pPolys;
}

BoundingPolygons *BoundingShapeManager::createBoundingPolygons(const std::string &name, Animation *pAnim, const Vec &grabPoint, float scale)
{
	Rect rect(pAnim->boundingBox());

	rect.sub(grabPoint);

	if(scale != 1.0f)
		rect.mult(scale);

	BoundingPolygons *pPolys = new BoundingPolygons(new PolygonGroup(new Polygon(rect)), name);
	m_shapes[name] = pPolys;

	return pPolys;
}
