layout (location = 0) in vec3 aPos;
uniform mat4 model;
void main()
{
	gl_Position = CameraProjection * CameraView * vec4(vec3(model * vec4(aPos, 1.0)), 1.0);
}