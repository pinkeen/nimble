/**
 * \file oglgraphics.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef OGLGRAPHICS_H
#define OGLGRAPHICS_H

#include <string>
#include <SDL/SDL.h>

#include "basicshaderprogram.h"
#include "../graphics.h"
#include "../polygons/polygon.h"
#include "../animationframe.h"

class OGLGraphics : public Graphics
{
	private:
		Color m_bcgColor;
		void onInit();

		BasicShaderProgram *m_pBasicShader;
		SDL_Surface *m_pScreenSurface;

	public:
		OGLGraphics(Configurator *pConfigurator);
                ~OGLGraphics();

		void setBackgroundColor(const Color &color);
		Image *createImageFromFile(const std::string &filename);
		void drawSprite(AnimationFrame *pFrame, const Vec &drawPosition, const Vec &grabPoint, Transformation &trans, const Color &tintColor, float opacity);
                void swapBuffers();
                void clearBuffer();
		void toggleFullscreen();

		void fillScreen(const Color &color);

		void drawPolygonOutline(const Polygon *pPolygon, const Color &color, const Vec &position);

};

#endif // OGLGRAPHICS_H
