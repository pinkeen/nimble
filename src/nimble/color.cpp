/**
 * \file color.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "color.h"

Color::Color(float r, float g, float b, float a)
{
	m_c = reinterpret_cast<RGBA*>(m_rgba);
	m_c->r = r;
	m_c->g = g;
	m_c->b = b;
	m_c->a = a;
}

Color::Color(float r, float g, float b)
{
	m_c = reinterpret_cast<RGBA*>(m_rgba);
	m_c->r = r;
	m_c->g = g;
	m_c->b = b;
	m_c->a = 0.0f;
}

Color::Color(const Color &color)
{
	m_c = reinterpret_cast<RGBA*>(m_rgba);
	assign(color);
}

Color::Color()
{
	m_c = reinterpret_cast<RGBA*>(m_rgba);
	memset(m_rgba, 0, sizeof(float) * 4);
}

