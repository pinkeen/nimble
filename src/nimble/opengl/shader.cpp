#include "shader.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../logger.h"

Shader::Shader(const char *alias, const char *source, ShaderType type)
        : m_alias(alias)
{
	m_log = 0;
	m_type = type;

	m_glHandle = createShaderGL(source, type);
}

Shader* Shader::createFromSource(const char *alias, const char *source, ShaderType type)
{
        return new Shader(alias, source, type);
}

Shader* Shader::createFromFile(const char *filename, ShaderType type)
{
        char *source = loadFile(filename);

        Shader *pShader = new Shader(filename, source, type);

        free(source);

        return pShader;
}


GLuint Shader::createShaderGL(const char *source, ShaderType type)
{
	GLenum glType;

	if(type == ST_VERTEX)
		glType = GL_VERTEX_SHADER;

	if(type == ST_FRAGMENT)
		glType = GL_FRAGMENT_SHADER;

	GLuint glHandle = glCreateShader(glType);

        ASSERT(glHandle != 0, "Could not create shader '%s'", source);

	glShaderSource(glHandle, 1, &source, 0);

	return glHandle;
}

char *Shader::loadFile(const char *filename)
{
	FILE *f = fopen(filename, "rb");

        ASSERT(f != 0, "Could not load file '%s'", filename);

	char *data = 0;
	size_t bytesRead = 0;
	size_t totalBytesRead = 0;
	size_t bufLen = 256;

	char buffer[bufLen];

	while((bytesRead = fread(buffer, 1, bufLen, f)) > 0)
	{
		data = static_cast<char*>(realloc(data, totalBytesRead + bytesRead));
		memcpy(data + totalBytesRead, buffer, bytesRead);

		totalBytesRead += bytesRead;
	}

	fclose(f);

	data = static_cast<char*>(realloc(data, totalBytesRead + 1));
	data[totalBytesRead] = '\0';

	return data;
}

bool Shader::compile()
{
	GLint status;

	glCompileShader(m_glHandle);
	glGetShaderiv(m_glHandle, GL_COMPILE_STATUS, &status);

	if(status == GL_TRUE)
		return true;


        WARN("Could not compile shader '%s' because:\n %s\n", m_alias, getLog());

	return false;
}

char *Shader::getLog()
{
	char *log;

	GLsizei logLen;
	GLsizei bufSize;

	glGetShaderiv(m_glHandle, GL_INFO_LOG_LENGTH, &bufSize);
	log = static_cast<char*>(malloc(bufSize));

	glGetShaderInfoLog(m_glHandle, bufSize, &logLen, log);

        if(m_log != 0)
                free(m_log);

        m_log = log;

        ASSERT((bufSize - 1) == logLen, "Could not read whole shader log");

	return log;
}

Shader::~Shader()
{

	glDeleteShader(m_glHandle);

	if(m_log != 0)
		free(m_log);
}
