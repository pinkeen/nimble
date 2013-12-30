#ifndef POLYGON_H
#define POLYGON_H

#include "../vector.h"
#include "../rect.h"
#include "../transformation.h"

#include <vector>

class Polygon
{
	private:
		std::vector<Vec> m_verts;

		typedef std::vector<Vec>::iterator VertIterator;
		typedef std::vector<Vec>::const_iterator ConstVertIterator;

		Rect m_bbox;

		inline void extendBBox(const Vec &v)
		{
			if(v.x() > m_bbox.bottomRight().x())
				m_bbox.bottomRight().x() = v.x();

			if(v.y() > m_bbox.bottomRight().y())
				m_bbox.bottomRight().y() = v.y();

			if(v.x() < m_bbox.topLeft().x())
				m_bbox.topLeft().x() = v.x();

			if(v.y() < m_bbox.topLeft().y())
				m_bbox.topLeft().y() = v.y();
		}

		inline static void projectionAxis(Vec &axis, const Vec &edgeA, const Vec &edgeB);
		inline static void projectedRange(const Vec &axis, const Vec &position, const Polygon &poly, float &min, float &max);

	public:
		Polygon();
		Polygon(const Polygon &polygon);
		Polygon(const Rect &rect);

		inline void addVertex(const Vec &vector)
		{
			m_verts.push_back(vector);

			if(m_verts.size() == 1)
			{
				m_bbox.set(vector, vector);
				return;
			}

			extendBBox(vector);
		}

		inline void addVertices(const std::vector<Vec> vertices)
		{
			m_verts.insert(m_verts.end(), vertices.begin(), vertices.end());

			ConstVertIterator it = vertices.begin();

			while(it != vertices.end())
			{
				extendBBox(*it);
				++it;
			}
		}

		inline const std::vector<Vec> &vertices() const { return m_verts; }
		inline unsigned int vertexCount() const { return m_verts.size(); }
		inline const Rect &boundingBox() const { return m_bbox; }

		bool isConvex();
		bool glueCommonEdge(const Polygon &polygon);

		bool intersects(Transformation &thisTrans, const Polygon &polygon, Transformation &otherTrans);

		void transformLinear(Transformation &trans);


};

#endif // POLYGON_H
