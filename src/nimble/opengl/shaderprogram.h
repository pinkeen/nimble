#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "shader.h"

#include <GL/glew.h>
#include <vector>

#include "../vector.h"
#include "../color.h"
#include "../matrix.h"


class ShaderProgram
{
	protected:
		GLuint m_glHandle;

		char *m_log;
                const char *m_alias;

		std::vector<GLuint> m_attributes;

		Shader *m_pVertexShader;
		Shader *m_pFragmentShader;

		GLuint registerAttribute(const char *name);
		void setAttributePointer(GLuint location, GLint size, float *pData);

                GLuint registerUniform(const char *name);
                inline void setUniform(GLuint location, int value) const
                        { glUniform1i(location, value); }

                inline void setUniform(GLuint location, float value) const
                        { glUniform1f(location, value); }

                inline void setUniform(GLuint location, const Vec &value) const
                        { glUniform2f(location, value.x(), value.y()); }

                inline void setUniform(GLuint location, const Color &value) const
			{ glUniform4f(location, value.r(), value.g(), value.b(), value.a()); }

		inline void setUniform(GLuint location, const Mat &value) const
			{
				const float mat[4] = {value.c11(), value.c12(), value.c21(), value.c22()};
				glUniformMatrix2fv(location, 1, 0, mat);
			}



		void disableAttributes();
		void enableAttributes();

                ShaderProgram(const char *alias);
                ShaderProgram(const char *alias, Shader *pVertexShader, Shader *pFragmentShader);

		void init();

		virtual void afterLink();
                virtual void onDisable();
                virtual void onUse();

                void attachShaders(Shader *pVertexShader, Shader *pFragmentShader);
                void freeShaders();

	public:
                void use();
                void disable();

                inline const char *alias() const { return m_alias; }
		virtual ~ShaderProgram();

		bool link();
                bool build();

		char *getLog();
};

#endif
