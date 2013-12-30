/**
 * \file oglimage.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef OGLIMAGE_H
#define OGLIMAGE_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>

#include "../image.h"

class OGLImage : public Image
{
	private:
		GLuint m_glHandle;
		GLuint loadFromFile(const std::string &filename);

	public:
		OGLImage(const std::string &filename);
                inline GLuint glHandle() const { return m_glHandle; }

		~OGLImage();

};

#endif // OGLIMAGE_H
