layout (location = 0) in vec3 aPos;
layout (location = 12) in mat4 aInstanceMatrix;
uniform mat4 model;
void main()
{
	mat4 matrix = aInstanceMatrix * model;
	gl_Position =  CameraProjection * CameraView * vec4(vec3(matrix * vec4(aPos, 1.0)), 1.0);
}