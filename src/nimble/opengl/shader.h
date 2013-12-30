#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader
{
	friend class ShaderProgram;

	public:
		typedef enum
		{
			ST_VERTEX,
			ST_FRAGMENT
		} ShaderType;

	private:
		GLuint m_glHandle;
		ShaderType m_type;
		char *m_log;
                const char *m_alias;

		GLuint createShaderGL(const char *source, ShaderType type);
                static char *loadFile(const char *filename);

        protected:
                Shader(const char *alias, const char *source, ShaderType type);

	public:
                static Shader* createFromFile(const char *filename, ShaderType type);
                static Shader* createFromSource(const char *alias, const char *source, ShaderType type);

		~Shader();

                inline const char *alias() const { return m_alias; }
                inline const GLuint glHandle() const { return m_glHandle; }

		bool compile();
		char *getLog();
};

#endif
