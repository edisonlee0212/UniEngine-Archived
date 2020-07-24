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
    vec4 lightFrustumWidth;
    vec4 lightFrustumDistance;
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
    int SoftShadowMode;
	float PCSSScaleFactor;
	float DisplaySplit;
	float SeamFixRatio;
    float VSMMaxVariance;
    float LightBleedFactor;
    float EVSMExponent;
    float AmbientLight;
};

//Material
struct Material{
	float shininess;
};

uniform Material material;
uniform bool enableSpecularMapping;
uniform bool enableNormalMapping;
//Textures
uniform sampler2D TEXTURE_DIFFUSE0;
uniform sampler2D TEXTURE_SPECULAR0;
uniform sampler2D TEXTURE_AMBIENT0;
uniform sampler2D TEXTURE_EMISSIVE0;
uniform sampler2D TEXTURE_HEIGHT0;
uniform sampler2D TEXTURE_NORMAL0;

//Shadow
uniform sampler2DArray directionalShadowMap;
uniform samplerCubeArrayShadow pointShadowMap;
uniform bool receiveShadow;
uniform bool enableSplitDisplay;
