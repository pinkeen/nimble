#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix.h"
#include "vector.h"
#include "utils.h"

#include <cmath>

// TODO: add shear and juicy stuff

class Transformation
{
	private:
		Mat m_mat;
		Vec m_position;
		Vec m_scale;
		Vec m_oldScale;

		Vec m_oldPosition;
		Vec m_positionDelta;

		float m_angle;
		float m_oldAngle;
		float m_asin;
		float m_acos;

		bool m_matgood;

		inline void updateASinACos()
		{
			m_asin = sinf(m_angle);
			m_acos = cosf(m_angle);
			m_matgood = false;
		}

		inline void updateMat()
		{
			if(m_matgood)
				return;

			m_mat.initRotScale(m_asin, m_acos, m_scale);
			m_matgood = true;
		}

	public:
		Transformation();
		Transformation(const Transformation &t);
		Transformation(const Vec &position);
		Transformation(const Vec &position, const Vec &scale);

		inline float angle() const { return m_angle; }
		inline float angleSin() const { return m_asin; }
		inline float angleCos() const { return m_acos; }

		inline const Vec& oldPosition() const { return m_oldPosition; }
		inline float oldAngle() const { return m_oldAngle; }
		inline const Vec &oldScale() const { return m_oldScale; }

		inline const Vec &scale() const { return m_scale; }

		inline void setScale(const Vec &s) { m_matgood = false; m_scale.assign(s);}

		inline void setScale(float x, float y)
		{
			m_matgood = false;
			m_scale.set(x, y);
		}

		inline void addScale(float x, float y, float lag)
		{
			m_matgood = false;
			m_scale.add(x * lag, y * lag);
		}

		inline void addScale(float v, float lag)
		{
			m_matgood = false;
			m_scale.add(v * lag);
		}

		inline const Vec &position() const { return m_position; }
		inline Vec &position() { return m_position; }

		inline const Mat &matrix() { updateMat(); return m_mat; }

		inline const Vec &positionDelta()
		{
			if(!m_position.equals(m_oldPosition))
			{
				m_positionDelta.assign(m_position);
				m_positionDelta.sub(m_oldPosition);
			}

			return m_positionDelta;
		}

		inline bool rotated() const { return m_angle == 0.0f; }
		inline bool scaled() const { return m_scale.x() == 1.0f && m_scale.y() == 1.0f; }

		inline bool transformed() const
		{
			return rotated() || scaled();
		}

		inline void setAngle(float angle)
		{
			m_angle = fmodf(angle, 2.0f * M_PI);
			updateASinACos();
		}

		inline void rotateBy(float angle)
		{
			m_angle = fmodf(m_angle + angle, 2.0f * M_PI);
			updateASinACos();
		}

		inline void rotateBy(float angle, float lag)
		{
			m_angle = fmodf(m_angle + angle * lag, 2.0f * M_PI);
			updateASinACos();
		}

		inline void setAngleDeg(float angle)
		{
			setAngle(Utils::degToRad(angle));
		}

		inline void rotateByDeg(float angle)
		{
			rotateBy(Utils::degToRad(angle));
		}

		inline void rotateByDeg(float angle, float lag)
		{
			rotateBy(Utils::degToRad(angle), lag);
		}


		inline void moveBy(const Vec &v) { m_position.add(v); }
		inline void moveBy(const Vec &v, float lag) { m_position.add(v.x() * lag, v.y() * lag); }

		inline void storeOld()
		{
			m_oldPosition.assign(m_position);
			m_oldAngle = m_angle;
			m_oldScale.assign(m_scale);
		}

		inline void transform(Vec &v)
		{
			updateMat();
			m_mat.multStore(v);
			v.add(m_position);
		}

		inline void transformLinear(Vec &v)
		{
			updateMat();
			m_mat.multStore(v);
		}

		inline void restorePosition()
		{
			m_position.assign(m_oldPosition);
			m_positionDelta.set(0.0f, 0.0f);
		}

		inline void restoreAngle()
		{
			m_angle = m_oldAngle;
		}

		inline void restoreScale()
		{
			m_scale = m_oldScale;
		}

		inline void restoreAll()
		{
			restorePosition();
			restoreAngle();
			restoreScale();
		}

};

#endif // TRANSFORMATION_H
