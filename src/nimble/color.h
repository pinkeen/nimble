/**
 * \file color.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef COLOR_H
#define COLOR_H

#include <cstring>
#include <cmath>

class Color
{
	private:
		typedef struct
		{
			float r;
			float g;
			float b;
			float a;
		} RGBA;

		float m_rgba[4];
		RGBA *m_c;

		inline void clamp(float *component)
		{
			if(*component > 1.0f)
			{
				*component = 1.0f;
				return;
			}

			if(*component < 0.0f)
				*component = 0.0f;
		}

		inline void wrap(float *component)
		{
			*component = *component - truncf(*component);

			if(*component < 0.0f)
				*component += 1.0f;
		}



	public:
		Color(float r, float g, float b, float a);
		Color(float r, float g, float b);
                Color();
		Color(const Color &color);

		inline float r() const { return m_c->r; }
		inline float g() const { return m_c->g; }
		inline float b() const { return m_c->b; }
		inline float a() const { return m_c->a; }

		inline float &r() { return m_c->r; }
		inline float &g() { return m_c->g; }
		inline float &b() { return m_c->b; }
		inline float &a() { return m_c->a; }


		inline unsigned char rUChar() const { return static_cast<unsigned char>(m_c->r * 255.0f); }
		inline unsigned char gUChar() const { return static_cast<unsigned char>(m_c->g * 255.0f); }
		inline unsigned char bUChar() const { return static_cast<unsigned char>(m_c->b * 255.0f); }
		inline unsigned char aUChar() const { return static_cast<unsigned char>(m_c->a * 255.0f); }

		inline void set(float r, float g, float b, float a)
		{
			m_c->r = r;
			m_c->g = g;
			m_c->b = b;
			m_c->a = a;
		}

		inline void set(float r, float g, float b)
		{
			m_c->r = r;
			m_c->g = g;
			m_c->b = b;
		}

		inline void add(const Color &color)
		{
			m_c->r += color.m_c->r;
			m_c->g += color.m_c->g;
			m_c->b += color.m_c->b;
			m_c->a += color.m_c->a;
		}

		inline void add(float r, float g, float b, float a)
		{
			m_c->r += r;
			m_c->g += g;
			m_c->b += b;
			m_c->a += a;
		}

		inline void add(float r, float g, float b)
		{
			m_c->r += r;
			m_c->g += g;
			m_c->b += b;
		}

		inline void assign(const Color &color) { memcpy(m_rgba, color.m_rgba, sizeof(float) * 4); }

		inline const float *rgbaPointer() const { return m_rgba; }

		inline void clamp() { clamp(&m_c->r); clamp(&m_c->g); clamp(&m_c->b); clamp(&m_c->a); }
		inline void wrap() { wrap(&m_c->r); wrap(&m_c->g); wrap(&m_c->b); wrap(&m_c->a); }
};

#endif // COLOR_H
