layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

//Lights
struct DirectionalLight {
    vec3 position;
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
    mat4 lightSpaceMatrix[4];
    vec4 lightFrustumWidth;
    vec4 lightFrustumDistance;
    vec4 ReservedParameters;
};

layout (std140, binding = 1) uniform DirectionalLightBlock
{
    int DirectionalLightCount;
    DirectionalLight DirectionalLights[DIRECTIONAL_LIGHTS_AMOUNT];
};
out vec4 FragPos; // FragPos from GS (output per emitvertex)
uniform int index;
void main()
{
    
    for(int split = 0; split < 4; ++split)
    {
        gl_Layer = index * 4 + split; // built-in variable that specifies to which face we render.
        for(int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            FragPos = gl_in[i].gl_Position;
            gl_Position = DirectionalLights[index].lightSpaceMatrix[split] * FragPos;
            EmitVertex();
        }
        EndPrimitive();
    }
} 