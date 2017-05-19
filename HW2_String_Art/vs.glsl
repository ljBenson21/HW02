#version 420 core  
                                                                  
void main(void)                                                   
{   
	float theta = float(gl_VertexID) / 10.0;
	float x, y;
	double pi = 3.14159;

	x = cos(60 * theta) * cos(theta) / 1;
	y = sin(1 * theta) * cos(theta) / 1;
                                                                  
	gl_Position = vec4(x, y, 0.0, 1.0);
}                                                                 