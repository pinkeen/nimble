/**
 * \file rect.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef RECT_H
#define RECT_H

#include <cmath>
#include "vector.h"
#include "transformation.h"
#include "macros.h"

class Rect
{
	private:
		Vec m_topLeft;
		Vec m_bottomRight;

	public:
		Rect(float x1, float y1, float x2, float y2);
                Rect(const Vec &topLeft, const Vec &bottomRight);
		Rect(const Rect &rect);
		Rect();

		inline const Vec &topLeft() const { return m_topLeft; }
		inline const Vec &bottomRight() const { return m_bottomRight; }

		inline Vec &topLeft() { return m_topLeft; }
		inline Vec &bottomRight() { return m_bottomRight; }


		inline void div(float val) { m_topLeft.div(val); m_bottomRight.div(val); }
		inline void norm(float maxX, float maxY) { m_topLeft.norm(maxX, maxY); m_bottomRight.norm(maxX, maxY); }

		void merge(const Rect &rect);

		inline void sub(const Vec &vec) { m_topLeft.sub(vec); m_bottomRight.sub(vec); }
		inline void add(const Vec &vec) { m_topLeft.add(vec); m_bottomRight.add(vec); }
		inline void mult(const Vec &vec) { m_topLeft.mult(vec); m_bottomRight.mult(vec); }
		inline void mult(float multiplier) { m_topLeft.mult(multiplier); m_bottomRight.mult(multiplier); }

		inline void set(const Vec &tl, const Vec &br)
		{
			m_topLeft.assign(tl);
			m_bottomRight.assign(br);
		}

		inline void assign(const Rect &rect)
		{
			m_topLeft.assign(rect.m_topLeft);
			m_bottomRight.assign(rect.m_bottomRight);
		}

                inline Vec size() const
                {
                        Vec sz(m_bottomRight);
                        sz.sub(m_topLeft);
                        sz.add(1.0f);
                        return sz;
                }

		inline bool notIntersects(const Rect &rect) const
		{
			return NOCOLLISION(m_topLeft.x(),
					   m_topLeft.y(),
					   m_bottomRight.x(),
					   m_bottomRight.y(),
					   rect.m_topLeft.x(),
					   rect.m_topLeft.y(),
					   rect.m_bottomRight.x(),
					   rect.m_bottomRight.y());
		}

		inline Vec center() const
		{
			Vec center(m_bottomRight);
			center.add(m_topLeft);
			center.div(2.0f);

			return center;
		}

		void transform(Transformation &trans);
		void transformLinear(Transformation &trans);
		void initFromBox(const Vec &v1, const Vec &v2, const Vec &v3, const Vec &v4);
};

#endif // RECT_H
