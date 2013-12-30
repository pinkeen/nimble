/**
 * \file oglgraphics.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */

#include "oglgraphics.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include "oglimage.h"
#include "../logger.h"
#include "../vector.h"

#include "../boundingpolygons.h"

static float quadVerts[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
static unsigned int quadTris[] = {0, 1, 2, 2, 3, 0};

OGLGraphics::OGLGraphics(Configurator *pConfigurator)
	: Graphics(pConfigurator)
{
	m_pBasicShader = 0;
}

OGLGraphics::~OGLGraphics()
{
	if(m_pBasicShader != 0)
		delete m_pBasicShader;
}

void OGLGraphics::onInit()
{
	m_pScreenSurface = SDL_SetVideoMode(m_resX, m_resY, 32,
					    SDL_OPENGL | (m_pConfigurator->fullscreen() ? SDL_FULLSCREEN : 0));

	ASSERT(m_pScreenSurface, "Could not set video mode %dx%dx32b.", m_resX, m_resY);

	GLenum err = glewInit();

	ASSERT(err == GLEW_OK, "Coult not init GLEW.");
	ASSERT(glewIsSupported("GL_VERSION_2_0"), "You need at least OpenGL 2.0");

	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1); //Vsync
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_TEXTURE_COORD_ARRAY);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(0, m_resX, m_resY, 0, -1, 1);
	glViewport(0, 0, m_resX, m_resY);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glPushMatrix();

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        glVertexPointer(2, GL_FLOAT, 0, quadVerts);

	if(m_pBasicShader != 0)
		delete m_pBasicShader;

	m_pBasicShader = new BasicShaderProgram();
	m_pBasicShader->build();
	m_pBasicShader->use();
}

void OGLGraphics::setBackgroundColor(const Color &color)
{
	m_bcgColor.assign(color);
	glClearColor(color.r(), color.g(), color.b(), color.a());
}

Image *OGLGraphics::createImageFromFile(const std::string &filename)
{
	Image *pImg = new OGLImage(filename);

	return pImg;
}

void OGLGraphics::drawSprite(AnimationFrame *pFrame, const Vec &drawPosition, const Vec &grabPoint,
			     Transformation &trans, const Color &tintColor, float opacity)
{
        const Rect &uvRect = pFrame->normTileRect();
	const Vec &uvTL = uvRect.topLeft();
	const Vec &uvBR = uvRect.bottomRight();

	const float quadUvs[8] = {uvTL.x(), uvTL.y(), uvBR.x(), uvTL.y(),
				  uvBR.x(), uvBR.y(), uvTL.x(), uvBR.y()};

        OGLImage *pImg = dynamic_cast<OGLImage*>(pFrame->image());

	Vec pos(drawPosition);
	pos.sub(pFrame->alignPoint());

	m_pBasicShader->setParams(pos, pFrame->size(), grabPoint, trans.matrix(), opacity, tintColor);

        glBindTexture(GL_TEXTURE_2D, pImg->glHandle());

        glTexCoordPointer(2, GL_FLOAT, 0, quadUvs);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, quadTris);

}

void OGLGraphics::drawPolygonOutline(const Polygon *pPolygon, const Color &color, const Vec &position)
{
	const std::vector<Vec> &verts = pPolygon->vertices();

	glUseProgram(0);

	glColor4f(color.r(), color.g(), color.b(), color.a());
	glLineWidth(1.0f);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBegin(GL_LINE_LOOP);

	for(std::vector<Vec>::const_iterator it = verts.begin();
		it != verts.end(); ++it)
	{
		glVertex2f(it->x() + position.x(), it->y() + position.y());
	}

	glEnd();

	m_pBasicShader->use();
}

void OGLGraphics::fillScreen(const Color &color)
{
	glBindTexture(GL_TEXTURE_2D, 0);

	float verts[] = {0.0f, 0.0f, m_resX, 0.0f, m_resX, m_resY, 0.0f, m_resY};

	glVertexPointer(2, GL_FLOAT, 0, verts);

	glUseProgram(0);

	glColor4f(color.r(), color.g(), color.b(), color.a());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, quadTris);

	m_pBasicShader->use();
	glVertexPointer(2, GL_FLOAT, 0, quadVerts);
}

void OGLGraphics::toggleFullscreen()
{
	m_fullscreen = !m_fullscreen;

	Uint32 flags = m_pScreenSurface->flags;

	SDL_FreeSurface(m_pScreenSurface);

	m_pScreenSurface = SDL_SetVideoMode(0, 0, 0, flags ^ SDL_FULLSCREEN);

	if(m_pScreenSurface == 0)
		m_pScreenSurface = SDL_SetVideoMode(0, 0, 0, flags);

	ASSERT(m_pScreenSurface != 0, "Failed to restore screen surface!");
}

void OGLGraphics::swapBuffers()
{
        SDL_GL_SwapBuffers();
}

void OGLGraphics::clearBuffer()
{
        glClear(GL_COLOR_BUFFER_BIT);
}
