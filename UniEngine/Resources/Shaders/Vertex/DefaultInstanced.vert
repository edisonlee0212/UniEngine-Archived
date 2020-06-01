layout (location = 0) in vec3 aPos;
layout (location = 5) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;


out vec2 TexCoords;


void main()
{
    TexCoords = aTexCoords;
    gl_Position = CameraProjection * CameraView * aInstanceMatrix * vec4(aPos, 1.0f); 
}