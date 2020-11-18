layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform int index;
void main()
{
    gl_Position = SpotLights[index].lightSpaceMatrix * model * vec4(aPos, 1.0);
}