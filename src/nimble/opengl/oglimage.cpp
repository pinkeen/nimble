/**
 * \file oglimage.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "oglimage.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../logger.h"

OGLImage::OGLImage(const std::string &filename) : Image()
{
	m_glHandle = loadFromFile(filename);
}

GLuint OGLImage::loadFromFile(const std::string &filename)
{
	SDL_Surface *s = IMG_Load(filename.c_str());

        ASSERT(s != 0, "Could not load image '%s': %s", filename.c_str(), SDL_GetError());

	m_width = s->w;
	m_height = s->h;

	unsigned int bpp = s->format->BitsPerPixel;

        ASSERT(bpp >= 24, "only > 24bit images are supported: '%s'", filename.c_str());

        m_bpp = bpp;

	GLint format;

	switch(bpp)
	{
                case 24:
			format = GL_RGB;
			m_hasAlpha = false;
		break;

                case 32:
			format = GL_RGBA;
			m_hasAlpha = true;
		break;
	}

	GLuint glHandle;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &glHandle);
	glBindTexture(GL_TEXTURE_2D, glHandle);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLfloat	glWrapParam = GL_CLAMP_TO_EDGE;

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrapParam);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrapParam);

        glTexImage2D(GL_TEXTURE_2D, 0, bpp / 8, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, s->pixels);

	SDL_FreeSurface(s);

	return glHandle;
}

OGLImage::~OGLImage()
{
	glDeleteTextures(1, &m_glHandle);
}
