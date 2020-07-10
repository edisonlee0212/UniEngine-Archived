layout (location = 0) out vec4 vFragColor;

//Lights
struct DirectionalLight {
    vec3 position;
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
    mat4 lightSpaceMatrix[4];
    vec4 ReservedParameters;
};

layout (std140, binding = 1) uniform DirectionalLightBlock
{
    int DirectionalLightCount;
    DirectionalLight DirectionalLights[DIRECTIONAL_LIGHTS_AMOUNT];
};


layout (std140, binding = 4) uniform ShadowSettings
{
    float SplitDistance0;
    float SplitDistance1;
    float SplitDistance2;
    float SplitDistance3;
    float EnableVSM;
	float EnableEVSM;
	float DisplaySplit;
	float SeamFixRatio;
    float VSMMaxVariance;
    float LightBleedFactor;
    float EVSMExponent;
    float Paddings;
};

uniform int index;

void main()
{
    float depth = gl_FragCoord.z;
    if(DirectionalLights[index].ReservedParameters.y != 0){
        if(EnableVSM != 0){
            if(EnableEVSM != 0){
                depth = depth * 2.0 - 1.0;
                float pos = exp(EVSMExponent * depth);
                float neg = -exp(-EVSMExponent * depth);
                vFragColor = vec4(pos, pos * pos, neg, neg * neg);
            }else{
                float dx = dFdx(depth);
                float dy = dFdy(depth);
                vFragColor = vec4(depth, depth * depth + 0.25 * (dx * dx + dy * dy), depth, 1);
            }
        }
    }else{
        vFragColor = vec4(depth, 0, 0, 1);
    }
}