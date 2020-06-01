layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 5) in vec2 aTexCoords;


out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;
    
    gl_Position = CameraProjection * CameraView * vec4(FragPos, 1.0);
}