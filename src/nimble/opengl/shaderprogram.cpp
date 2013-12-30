#include "shaderprogram.h"

#include <cassert>
#include <cstdlib>

#include "../logger.h"

ShaderProgram::ShaderProgram(const char *alias)
        : m_alias(alias)
{
	init();
}

ShaderProgram::ShaderProgram(const char *alias, Shader *pVertexShader, Shader *pFragmentShader)
        : m_alias(alias)
{
	init();
	attachShaders(pVertexShader, pFragmentShader);
}

void ShaderProgram::init()
{
	m_log = 0;
	m_pVertexShader = 0;
	m_pFragmentShader = 0;
	m_glHandle = glCreateProgram();
}

void ShaderProgram::attachShaders(Shader *pVertexShader, Shader *pFragmentShader)
{
        ASSERT(pVertexShader->m_type == Shader::ST_VERTEX, "Expected vertex shader");
        ASSERT(pFragmentShader->m_type == Shader::ST_FRAGMENT, "Expected fragment shader");

        glAttachShader(m_glHandle, pVertexShader->glHandle());
        glAttachShader(m_glHandle, pFragmentShader->glHandle());

        freeShaders();

	m_pVertexShader = pVertexShader;
	m_pFragmentShader = pFragmentShader;
}

bool ShaderProgram::link()
{
	GLint status;

	glLinkProgram(m_glHandle);

	glGetProgramiv(m_glHandle, GL_LINK_STATUS, &status);

	if(status == GL_TRUE)
	{
		afterLink();
		return true;
	}

        WARN("Could not link shader program '%s' because:\n %s", m_alias, getLog());

	return false;
}

bool ShaderProgram::build()
{
        bool r1 = m_pVertexShader->compile();
        bool r2 = m_pFragmentShader->compile();
        bool r3 = link();

        return r1 && r2 && r3;
}

char *ShaderProgram::getLog()
{
	char *log;

	GLsizei logLen;
	GLsizei bufSize;

	glGetProgramiv(m_glHandle, GL_INFO_LOG_LENGTH, &bufSize);
	log = static_cast<char*>(malloc(bufSize));

	glGetProgramInfoLog(m_glHandle, bufSize, &logLen, log);

        if(m_log != 0)
                free(m_log);

        m_log = log;

        ASSERT((bufSize - 1) == logLen, "Could not read whole shader log");

	return log;
}

ShaderProgram::~ShaderProgram()
{
        freeShaders();

	glDeleteProgram(m_glHandle);

	if(m_log)
		free(m_log);
}

void ShaderProgram::onUse()
{
}

void ShaderProgram::onDisable()
{
}


void ShaderProgram::disableAttributes()
{
	for(std::vector<GLuint>::iterator loc = m_attributes.begin(); loc != m_attributes.end(); ++loc)
		glDisableVertexAttribArray(*loc);
}

void ShaderProgram::enableAttributes()
{
	for(std::vector<GLuint>::iterator loc = m_attributes.begin(); loc != m_attributes.end(); ++loc)
		glEnableVertexAttribArray(*loc);
}

GLuint ShaderProgram::registerAttribute(const char *name)
{
	GLuint loc = glGetAttribLocation(m_glHandle, name);
	m_attributes.push_back(loc);
	return loc;
}

void ShaderProgram::setAttributePointer(GLuint location, GLint size, float *pData)
{
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, pData);
}

void ShaderProgram::freeShaders()
{
        if(m_pVertexShader != 0)
                delete m_pVertexShader;

        if(m_pFragmentShader != 0)
                delete m_pFragmentShader;
}

GLuint ShaderProgram::registerUniform(const char *name)
{
	return glGetUniformLocation(m_glHandle, name);
}

void ShaderProgram::use()
{
        glUseProgram(m_glHandle);
        onUse();
}

void ShaderProgram::disable()
{
        onDisable();
}

void ShaderProgram::afterLink() {}
