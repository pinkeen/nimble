/**
 * \file vector.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "macros.h"

class Vec
{
	private:
		float m_x;
		float m_y;

	public:
		Vec(float y, float x);
		Vec(const Vec &vector);
		Vec();

		inline const float &x() const { return m_x; }
		inline const float &y() const { return m_y; }
		inline float &x() { return m_x; }
		inline float &y() { return m_y; }

		inline void div(float val) { m_x /= val; m_y /= val; }
                inline void mult(float val) { m_x *= val; m_y *= val; }
		inline void mult(float vx, float vy) { m_x *= vx; m_y *= vy; }
		inline void mult(const Vec &oVec) { m_x *= oVec.m_x; m_y *= oVec.m_y; }
		inline void norm(float maxX, float maxY) { m_x /= maxX; m_y /= maxY; }
                inline void norm() { float l = length(); m_x /= l; m_y /= l; }
                inline float length() const { return sqrt(m_x * m_x + m_y * m_y); }
		inline void add(const Vec &oVec) { m_x += oVec.m_x; m_y += oVec.m_y; }
                inline void add(float v) { m_x += v; m_y += v; }
		inline void add(float dx, float dy) { m_x += dx; m_y += dy; }
		inline void sub(const Vec &oVec) { m_x -= oVec.m_x; m_y -= oVec.m_y; }
		inline void sub(float v) { m_x -= v; m_y -= v; }
		inline void sub(float dx, float dy) { m_x -= dx; m_y -= dy; }

		inline float cross(const Vec &oVec) const { return m_x * oVec.m_y - m_y * oVec.m_x; }
		inline float dot(const Vec &oVec) const { return m_x * oVec.m_x + m_y * oVec.m_y; }
		inline void assign(const Vec &oVec) { m_x = oVec.m_x; m_y = oVec.m_y; }
		inline void set(float x, float y) { m_x = x; m_y = y; }

		inline bool equals(const Vec &oVec) const { return m_x == oVec.m_x && m_y == oVec.m_y; }
		inline bool equals(const Vec &oVec, float eps) const { return (fabsf(m_x - oVec.m_x) < eps) && (fabsf(m_y - oVec.m_y) < eps); }

		inline void rot(float sina, float cosa)
		{
			float x = m_x * cosa - m_y * sina;
			float y = m_x * sina + m_y * cosa;

			m_x = x;
			m_y = y;
		}

		inline void rot(float angleRads)
			{ rot(sinf(angleRads), cosf(angleRads)); }

		inline float projectionSpaceCoord(const Vec &oVec) const
		{
			return dot(oVec) / dot(*this);
		}

		inline void projectOnto(const Vec &oVec)
		{
			float fact = projectionSpaceCoord(oVec);
			m_x = fact * oVec.m_x;
			m_y = fact * oVec.m_y;
		}

		inline void perp()
		{
			float tmp = m_x;
			m_x = -m_y;
			m_y = tmp;
		}
};

#endif // VECTOR_H
