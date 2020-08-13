layout (location = 0) in vec3 aPos;
layout (location = 12) in mat4 aInstanceMatrix;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = lightSpaceMatrix * (model * aInstanceMatrix) * vec4(aPos, 1.0);
}