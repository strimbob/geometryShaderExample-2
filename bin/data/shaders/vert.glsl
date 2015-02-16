#version 120
varying vec2 texCoordVarying;
void main()
{
	gl_FrontColor =  gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
    texCoordVarying = gl_MultiTexCoord0.xy;
	gl_Position = gl_Vertex;
}
