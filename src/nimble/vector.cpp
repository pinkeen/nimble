/**
 * \file vector.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "vector.h"

Vec::Vec(float x, float y) :
	m_x(x), m_y(y)
{
}

Vec::Vec(const Vec &vector) : m_x(vector.m_x), m_y(vector.m_y) {}
Vec::Vec() : m_x(0.0f), m_y(0.0f) {}

