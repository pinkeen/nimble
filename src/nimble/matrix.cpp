#include "matrix.h"

Mat::Mat()
	: m_11(1.0f), m_21(0.0f), m_12(0.0f), m_22(1.0f)
{
}

Mat::Mat(float c11, float c21, float c12, float c22)
	: m_11(c11), m_21(c21), m_12(c12), m_22(c22)
{
}

Mat::Mat(const Vec &v1, const Vec &v2)
	: m_11(v1.x()), m_21(v1.y()), m_12(v2.x()), m_22(v2.y())
{

}
