//Camera
layout (std140, binding = 0) uniform MainCameraBlock
{
    mat4 CameraProjection;
    mat4 CameraView;
    vec4 CameraReservedParameters;
    vec3 CameraPosition;
};

//Lights
struct DirectionalLight {
    vec3 position;
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
    mat4 lightSpaceMatrix[4];
    vec4 ReservedParameters;
};

struct PointLight {
    vec3 position;
    vec4 constantLinearQuadFarPlane;
    vec3 diffuse;
    vec3 specular;
    mat4 lightSpaceMatrix[6];
    vec4 ReservedParameters;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 diffuse;
    vec3 specular;       
};

layout (std140, binding = 1) uniform DirectionalLightBlock
{
    int DirectionalLightCount;
    DirectionalLight DirectionalLights[DIRECTIONAL_LIGHTS_AMOUNT];
};

layout (std140, binding = 2) uniform PointsLightBlock
{
    int PointLightCount;
    PointLight PointLights[POINT_LIGHTS_AMOUNT];
};

layout (std140, binding = 3) uniform SpotLightBlock
{
    int SpotLightCount;
    SpotLight SpotLights[SPOT_LIGHTS_AMOUNT];
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
};

//Material
struct Material{
	float shininess;
};

uniform Material material;

//Textures
uniform sampler2D TEXTURE_DIFFUSE[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_SPECULAR[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_AMBIENT[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_EMISSIVE[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_HEIGHT[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_NORMAL[MAX_TEXTURES_AMOUNT];

//Shadow
uniform sampler2DArray directionalShadowMap;
uniform samplerCubeArrayShadow pointShadowMap;
uniform bool receiveShadow;
uniform bool enableSplitDisplay;
