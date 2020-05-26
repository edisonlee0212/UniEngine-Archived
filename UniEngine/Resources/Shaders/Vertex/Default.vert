layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord0;


uniform mat4 model;
out vec2 TexCoords;
void main()
{
    TexCoords = aTexCoord0;    
    gl_Position = CameraProjection * CameraView * model * vec4(aPos, 1.0);
}