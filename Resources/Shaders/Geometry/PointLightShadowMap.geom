layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

struct PointLight {
    vec3 position;
    vec4 constantLinearQuadFarPlane;
    vec3 diffuse;
    vec3 specular;
    mat4 lightSpaceMatrix[6];
    vec4 ReservedParameters;
};

layout (std140, binding = 2) uniform PointsLightBlock
{
    int PointLightCount;
    PointLight PointLights[POINT_LIGHTS_AMOUNT];
};


uniform int index;
out vec4 FragPos; // FragPos from GS (output per emitvertex)
void main()
{
    for(int face = 0; face < 6; ++face)
    {
        gl_Layer = index * 6 + face; // built-in variable that specifies to which face we render.
        for(int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            FragPos = gl_in[i].gl_Position;
            gl_Position = PointLights[index].lightSpaceMatrix[face] * FragPos;
            EmitVertex();
        }    
        EndPrimitive();
    }
} 