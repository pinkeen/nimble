/**
 * \file rect.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "rect.h"
#include "logger.h"
#include "polygons/polygon.h"

Rect::Rect(float x1, float y1, float x2, float y2)
        : m_topLeft(x1, y1), m_bottomRight(x2, y2)
{
}

Rect::Rect(const Vec &topLeft, const Vec &bottomRight)
        : m_topLeft(topLeft), m_bottomRight(bottomRight)
{
}

Rect::Rect(const Rect &rect) : m_topLeft(rect.m_topLeft),
	m_bottomRight(rect.m_bottomRight) {}

Rect::Rect() {}

void Rect::merge(const Rect &rect)
{
	if(rect.m_topLeft.x() < m_topLeft.x())
		m_topLeft.x() = rect.topLeft().x();

	if(rect.m_topLeft.y() < m_topLeft.y())
		m_topLeft.y() = rect.topLeft().y();

	if(rect.m_bottomRight.x() > m_bottomRight.x())
		m_bottomRight.x() = rect.m_bottomRight.x();

	if(rect.m_bottomRight.y() > m_bottomRight.y())
		m_bottomRight.y() = rect.m_bottomRight.y();
}

void Rect::initFromBox(const Vec &v1, const Vec &v2, const Vec &v3, const Vec &v4)
{
	float nx1 = MIN(MIN(v1.x(), v2.x()),
			MIN(v3.x(), v4.x()));
	float ny1 = MIN(MIN(v1.y(), v2.y()),
			MIN(v3.y(), v4.y()));

	float nx2 = MAX(MAX(v1.x(), v2.x()),
			MAX(v3.x(), v4.x()));
	float ny2 = MAX(MAX(v1.y(), v2.y()),
			MAX(v3.y(), v4.y()));

	m_topLeft.set(nx1, ny1);
	m_bottomRight.set(nx2, ny2);
}

void Rect::transform(Transformation &trans)
{
	Vec topRight(m_bottomRight.x(), m_topLeft.y());
	Vec bottomLeft(m_topLeft.x(), m_bottomRight.y());

	trans.transform(m_topLeft);
	trans.transform(m_bottomRight);
	trans.transform(topRight);
	trans.transform(bottomLeft);

	initFromBox(m_topLeft, m_bottomRight, topRight, bottomLeft);
}

void Rect::transformLinear(Transformation &trans)
{
	Vec topRight(m_bottomRight.x(), m_topLeft.y());
	Vec bottomLeft(m_topLeft.x(), m_bottomRight.y());

	trans.transformLinear(m_topLeft);
	trans.transformLinear(m_bottomRight);
	trans.transformLinear(topRight);
	trans.transformLinear(bottomLeft);

	initFromBox(m_topLeft, m_bottomRight, topRight, bottomLeft);
}

