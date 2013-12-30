#include "basicshaderprogram.h"

static const char vertexShaderSource[] =
                "\
		uniform mat2 transmat;\
                uniform vec2 position;\
                uniform vec2 size;\
                uniform vec2 grabPoint;\
                \
                uniform mat4 gl_ModelViewMatrix;\
                uniform mat4 gl_ProjectionMatrix;\
                attribute vec4 gl_Vertex;\
                \
                void main() {\
			vec2 fpos = transmat * (gl_Vertex.xy * size - grabPoint) + position;\
                        gl_Position = gl_ProjectionMatrix * vec4(fpos, 0, 1);\
                        gl_TexCoord[0] = gl_MultiTexCoord0;\
                }\
                ";


static const char fragmentShaderSource[] =
                "\
                \
                uniform vec4 tintColor;\
                uniform float opacity;\
                \
                uniform sampler2D tex; \
                \
                void main(void) \
                {\
                        vec4 texel = texture2D(tex, gl_TexCoord[0].st);\
			vec3 color = mix(texel.rgb, tintColor.rgb, tintColor.a);\
                        gl_FragColor = vec4(color, texel.a * opacity); \
                }\
                ";

BasicShaderProgram::BasicShaderProgram()
        : ShaderProgram("basicShaderProgram")
{
        Shader *pVS = Shader::createFromSource("basicVertexShader", vertexShaderSource, Shader::ST_VERTEX);
        Shader *pFS = Shader::createFromSource("basicFragmentShader", fragmentShaderSource, Shader::ST_FRAGMENT);

        attachShaders(pVS, pFS);
}

void BasicShaderProgram::afterLink()
{
        m_tintColorLoc = registerUniform("tintColor");
	m_posLoc = registerUniform("position");
        m_sizeLoc = registerUniform("size");
	m_grabPointLoc = registerUniform("grabPoint");
        m_opacityLoc = registerUniform("opacity");
	m_matLoc = registerUniform("transmat");
}

void BasicShaderProgram::onUse()
{

}


