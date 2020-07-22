layout (location = 0) out vec4 vFragColor;

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


layout (std140, binding = 4) uniform ShadowSettings
{
	float SplitDistance0;
	float SplitDistance1;
	float SplitDistance2;
	float SplitDistance3;
	int SoftShadowMode;
	float PCSSScaleFactor;
	float DisplaySplit;
	float SeamFixRatio;
	float VSMMaxVariance;
	float LightBleedFactor;
	float EVSMExponent;
	float Padding0;
};

uniform int index;

void main()
{
	float depth = gl_FragCoord.z;
	switch(SoftShadowMode){
		case 1:
			vFragColor = vec4(depth, depth * depth, 0, 1);
			break;
		case 2:
			vFragColor = vec4(exp(depth * EVSMExponent), 0, 0, 1);
			break;
		default:
			vFragColor = vec4(depth, 0, 0, 1);
			break;
	}
}