#ifndef BOUNDINGSHAPEMANAGER_H
#define BOUNDINGSHAPEMANAGER_H

#include <map>
#include <string>

#include "boundingshape.h"
#include "boundingpolygons.h"
#include "animation.h"

class BoundingShapeManager
{
	private:
		std::map<std::string, BoundingShape*> m_shapes;

		typedef std::map<std::string, BoundingShape*>::iterator ShapePIterator;
		typedef std::map<std::string, BoundingShape*>::const_iterator ConstShapePIterator;

	public:
		BoundingShapeManager();
		~BoundingShapeManager();

		BoundingPolygons *createBoundingPolygons(const std::string &name, PolygonGroup *pGroup);
		BoundingPolygons *createBoundingPolygons(const std::string &name, Polygon *pPolygon);
		BoundingPolygons *createBoundingPolygons(const std::string &name, const Rect &rect);
		BoundingPolygons *createBoundingPolygons(const std::string &name, Animation *pAnim, float scale);
		BoundingPolygons *createBoundingPolygons(const std::string &name, Animation *pAnim, const Vec &grabPoint, float scale);

		BoundingShape *shape(const std::string &name) const;

		void freeAll();
};

#endif // BOUNDINGSHAPEMANAGER_H
