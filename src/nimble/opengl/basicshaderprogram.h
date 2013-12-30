#ifndef BASICSHADERPROGRAM_H
#define BASICSHADERPROGRAM_H

#include "shaderprogram.h"
#include "../logger.h"
#include "../matrix.h"

class BasicShaderProgram : public ShaderProgram
{
        private:
                GLuint m_tintColorLoc;
                GLuint m_posLoc;
                GLuint m_sizeLoc;
                GLuint m_grabPointLoc;
                GLuint m_opacityLoc;
		GLuint m_matLoc;

                void afterLink();
                void onUse();

        public:
                BasicShaderProgram();

		inline void setParams(const Vec &pos, const Vec &size, const Vec &grabPoint,
				      const Mat &mat, float opacity, const Color &tintColor) const
                {
                        setUniform(m_posLoc, pos);
                        setUniform(m_sizeLoc, size);
			setUniform(m_grabPointLoc, grabPoint);
			setUniform(m_opacityLoc, opacity);
                        setUniform(m_tintColorLoc, tintColor);
			setUniform(m_matLoc, mat);
                }

};

#endif // BASICSHADERPROGRAM_H
