/***********************************************
 Geometry shader to convert lines into triangle strips
 Memo Akten
 www.memo.tv

************************************************/

#version 120

#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#extension GL_EXT_geometry_shader4 : enable

uniform float thickness;
uniform vec3 lightDir;
uniform sampler2DRect spark;
varying vec2 texCoordVarying;
varying vec2 texCoordVaryingQ;
uniform float imgWidth, imgHeight;
varying vec3 lightDirQ;
uniform vec3 gCameraPos;

void main() {
	vec3 p0 = gl_PositionIn[0].xyz;
	//vec3 p1 = gl_PositionIn[1].xyz; //
    
    
    
    vec3 toCamera = normalize(gCameraPos - p0);
    vec3 upa = vec3(0.0, 1.0, 0.0);
    vec3 rightA = cross(toCamera, upa);
    
    
    
		vec3 p1 = vec3(1,1,1); // sameWAY
	vec3 up = vec3(1, 1, 1);	// arbitrary up vector
	
	vec3 dir = normalize(gCameraPos - p0);			// normalized direction vector from p0 to p1
	vec3 right = normalize(cross(dir, up));	// right vector
	vec3 norm = cross(right, dir);
	float fColMult = abs(dot(norm, lightDir));
	vec4 colMult = vec4(fColMult, fColMult, fColMult, 1.0);
	
    texCoordVaryingQ = texCoordVarying;

	right *= thickness;

    
    mat4 frontFacing = gl_ModelViewProjectionMatrix ;
	
    gl_Position =  frontFacing * vec4(p0 - right, 1.0);
	gl_FrontColor = gl_FrontColorIn[0] * colMult;
    gl_TexCoord[0].x = 0;
    gl_TexCoord[0].y = 0;
	EmitVertex();
    
    

	
	gl_Position = frontFacing * vec4(p0 + right, 1.0);
    gl_TexCoord[0].x = 100;
    gl_TexCoord[0].y = 0;
	gl_FrontColor = gl_FrontColorIn[0] * colMult;
	EmitVertex();
    
    gl_Position = frontFacing * vec4((p0+20) - right, 1.0);
    gl_TexCoord[0].x =  0;
    gl_TexCoord[0].y = 100.0;
	EmitVertex();
    
	gl_Position = frontFacing * vec4((p0+20) + right, 1.0);

    
    gl_TexCoord[0].x = 100;
    gl_TexCoord[0].y = 100;
	EmitVertex();
    
    
    lightDirQ = gl_FrontColorIn[0].xyz * colMult.xyz;

    
    

}