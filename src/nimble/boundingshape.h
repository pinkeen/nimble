#ifndef BOUNDINGSHAPE_H
#define BOUNDINGSHAPE_H

#include <string>
#include "vector.h"
#include "rect.h"
#include "transformation.h"

class BoundingShape
{
	public:
		typedef enum
		{
			T_CIRCLE,
			T_POLYGON
		} Type;

	private:
		std::string m_name;

	protected:
		Rect m_bbox;
		Type m_type;

	public:
		BoundingShape(Type type, const std::string &name);
		virtual ~BoundingShape() {}

		virtual bool intersects(Transformation &thisTrans, const BoundingShape *pShape, Transformation &otherTrans) const = 0;

		inline const Rect &boundingBox() const { return m_bbox; }
		inline const Type &type() const { return m_type; }
		inline const std::string &name() const { return m_name; }


};

#endif // BOUNDINGSHAPE_H
