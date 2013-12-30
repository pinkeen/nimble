#include "transformation.h"

Transformation::Transformation()
	:  m_scale(1.0f, 1.0f), m_oldScale(1.0f, 1.0f), m_angle(0.0f), m_oldAngle(0.0f), m_asin(0.0f), m_acos(1.0f), m_matgood(true)
{
}


Transformation::Transformation(const Transformation &t)
	:
	m_mat(t.m_mat),
	m_position(t.m_position),
	m_scale(t.m_scale),
	m_oldScale(t.m_oldScale),
	m_oldPosition(t.m_oldPosition),
	m_positionDelta(t.m_positionDelta),
	m_angle(t.m_angle),
	m_oldAngle(t.m_oldAngle),
	m_asin(t.m_asin),
	m_acos(t.m_acos),
	m_matgood(t.m_matgood)
{
}

Transformation::Transformation(const Vec &position)
	:  m_position(position), m_scale(1.0f, 1.0f), m_oldScale(1.0f, 1.0f), m_oldPosition(position), m_angle(0.0f), m_oldAngle(0.0f), m_asin(0.0f), m_acos(1.0f), m_matgood(true)

{
}

Transformation::Transformation(const Vec &position, const Vec &scale)
	:  m_position(position), m_scale(scale), m_oldScale(scale), m_oldPosition(position), m_angle(0.0f), m_oldAngle(0.0f), m_asin(0.0f), m_acos(1.0f), m_matgood(true)
{
}

