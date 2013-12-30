#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

#include <cmath>

class Mat
{
	private:
		float m_11;
		float m_21;
		float m_12;
		float m_22;

	public:
		Mat();
		Mat(float c11, float c21, float c12, float c22);
		Mat(const Vec &v1, const Vec &v2);


		inline float c11() const { return m_11; }
		inline float c21() const { return m_21; }
		inline float c12() const { return m_12; }
		inline float c22() const { return m_22; }

		inline void add(float v)
		{
			m_11 += v;
			m_21 += v;
			m_12 += v;
			m_22 += v;
		}

		inline void sub(float v)
		{
			m_11 += v;
			m_21 += v;
			m_12 += v;
			m_22 += v;
		}

		inline void div(float v)
		{
			m_11 /= v;
			m_21 /= v;
			m_12 /= v;
			m_22 /= v;
		}

		inline void mult(float v)
		{
			m_11 *= v;
			m_21 *= v;
			m_12 *= v;
			m_22 *= v;
		}

		inline void mult(const Mat &o)
		{
			m_11 = m_11 * o.m_11 + m_21 * o.m_12;
			m_21 = m_11 * o.m_21 + m_21 * o.m_22;
			m_12 = m_12 * o.m_11 + m_22 * o.m_12;
			m_22 = m_12 * o.m_21 + m_22 * o.m_22;
		}

		inline Vec mult(const Vec &v)
		{
			return Vec(m_11 * v.x() + m_21 * v.y(),
				   m_12 * v.x() + m_22 * v.y());
		}

		inline void multStore(Vec &v)
		{
			float x = m_11 * v.x() + m_21 * v.y();
			float y = m_12 * v.x() + m_22 * v.y();
			v.set(x, y);
		}

		inline float det() const
		{
			return m_11 * m_22 - m_21 * m_12;
		}

		inline void inv()
		{
			float d = det();
			float tmp = m_11;
			m_11 = m_22;
			m_22 = tmp;
			m_12 = -m_12;
			m_21 = -m_21;
			div(d);
		}

		inline void scale(const Vec &scale)
		{
			m_11 *= scale.x();
			m_21 *= scale.y();
			m_12 *= scale.x();
			m_22 *= scale.y();
		}

		inline void initRot(float sina, float cosa)
		{
			m_11 = cosa;
			m_21 = -sina;
			m_12 = sina;
			m_22 = cosa;
		}

		inline void initScale(const Vec &s)
		{
			m_11 = s.x();
			m_22 = s.y();
			m_21 = m_12 = 0.0f;
		}

		inline void initRotScale(float sin, float cos, const Vec &s)
		{
			initRot(sin, cos);
			scale(s);
		}



};

#endif // MATRIX_H
