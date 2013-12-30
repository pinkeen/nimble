/**
 * \file graphics.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <map>

#include "configurator.h"
#include "vector.h"
#include "color.h"
#include "image.h"
#include "sprite.h"
#include "transformation.h"
#include "polygons/polygon.h"

class Configurator;

class Graphics
{
	protected:
                virtual Image *createImageFromFile(const std::string &filename) = 0;

		friend class ImageManager;

		virtual void onInit() = 0;

		Configurator *m_pConfigurator;

		int m_resX;
		int m_resY;

		bool m_fullscreen;

	public:
		Graphics(Configurator *pConfigurator);
		virtual ~Graphics() {}

		void init();

		virtual void setBackgroundColor(const Color &color) = 0;
		virtual void drawSprite(AnimationFrame *pFrame, const Vec &drawPosition, const Vec &grabPoint, Transformation &trans, const Color &tintColor, float opacity) = 0;
                virtual void swapBuffers() = 0;
                virtual void clearBuffer() = 0;

		virtual void fillScreen(const Color &color) = 0;
		virtual void toggleFullscreen() = 0;

		inline bool fullscreen() const { return m_fullscreen; }

		virtual void drawPolygonOutline(const Polygon *pPolygon, const Color &color, const Vec &position) = 0;
};

#endif // GRAPHICS_H
