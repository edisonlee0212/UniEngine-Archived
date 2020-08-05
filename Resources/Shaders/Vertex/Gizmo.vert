layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 scaleMatrix;
void main()
{
	gl_Position = CameraProjection * CameraView * vec4(vec3(model * scaleMatrix * vec4(aPos, 1.0)), 1.0);
}