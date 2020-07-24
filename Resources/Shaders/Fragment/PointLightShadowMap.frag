in vec4 FragPos;

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

void main()
{
    float lightDistance = length(FragPos.xyz - PointLights[index].position);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / PointLights[index].constantLinearQuadFarPlane.w;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}