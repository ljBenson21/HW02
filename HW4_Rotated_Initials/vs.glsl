#version 420 core  
#extension GL_ARB_explicit_uniform_location : enable

layout(location = 0) in vec4 offset;
layout(location = 1) uniform vec3 theta;
                                                                  
void main(void)                                                   
{     
	double pi = 3.14159;
	vec3 angles = radians(theta);
	vec3 c = cos(theta);
	vec3 s = sin(2 * theta) * 1.5;

	const vec4 vertices[] = vec4[](vec4(-0.25, 0.25, 0.5, 1.0),
		vec4(-0.25, -0.15, 0.5, 1.0),
		vec4(-0.2, 0.25, 0.5, 1.0),
		vec4(-0.25, -0.15, 0.5, 1.0),
		vec4(-0.15, -0.1, 0.5, 1.0),
		vec4(-0.15, -0.15, 0.5, 1.0),
		vec4(0.0, 0.25, 0.5, 1.0),
		vec4(0.05, 0.25, 0.5, 1.0),
		vec4(0.05, -0.15, 0.5, 1.0),
		vec4(0.05, -0.15, 0.5, 1.0),
		vec4(-0.07, 0.0, 0.5, 1.0),
		vec4(-0.05, -0.1, 0.5, 1.0)
	);


	mat4 rotate_z = mat4(c.z, -s.z, 0.0, 0.0,
		s.z, c.z, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);

	mat4 scale = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
                                                                  
    gl_Position = vertices[gl_VertexID] * rotate_z * scale;                          
}                                                                 