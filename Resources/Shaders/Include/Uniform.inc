#extension GL_ARB_bindless_texture : require

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
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
	mat4 lightSpaceMatrix[4];
	vec4 lightFrustumWidth;
	vec4 lightFrustumDistance;
	vec4 ReservedParameters;
	int viewPortXStart;
	int viewPortYStart;
	int viewPortXSize;
	int viewPortYSize;
};

struct PointLight {
	vec3 position;
	vec4 constantLinearQuadFarPlane;
	vec3 diffuse;
	vec3 specular;
	mat4 lightSpaceMatrix[6];
	vec4 ReservedParameters;
	int viewPortXStart;
	int viewPortYStart;
	int viewPortXSize;
	int viewPortYSize;
};

struct SpotLight {
	vec3 position;
	float SpotLightPadding0;
	vec3 direction;
	float SpotLightPadding1;
	mat4 lightSpaceMatrix;
	vec4 cutOffOuterCutOffLightSizeBias;
	vec4 constantLinearQuadFarPlane;
	vec3 diffuse;
	float SpotLightPadding2;
	vec3 specular;
	float SpotLightPadding3;
	int viewPortXStart;
	int viewPortYStart;
	int viewPortXSize;
	int viewPortYSize;
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

layout (std140, binding = 4) uniform LightSettingsBlock
{
	float SplitDistance0;
	float SplitDistance1;
	float SplitDistance2;
	float SplitDistance3;
	int PCSSPCFSampleAmount;
	float PCSSScaleFactor;
	int PCSSBSAmount;
	float SeamFixRatio;
	float VSMMaxVariance;
	float LightBleedFactor;
	float EVSMExponent;
	float AmbientLight;
};

layout (std140, binding = 5) uniform KernelBlock
{
	vec4 UniformKernel[MAX_KERNEL_AMOUNT];
	vec4 GaussianKernel[MAX_KERNEL_AMOUNT];
};

layout (std140, binding = 6) uniform TextureBindings
{
	sampler2D TEXTURE_DIFFUSE0;
	sampler2D TEXTURE_SPECULAR0;
	sampler2D TEXTURE_AMBIENT0;
	sampler2D TEXTURE_EMISSIVE0;
	sampler2D TEXTURE_HEIGHT0;
	sampler2D TEXTURE_NORMAL0;
	sampler2D spotShadowMap;
	sampler2DArray directionalShadowMap;
	sampler2DArray pointShadowMap;
	
};

//Material
struct Material{
	float shininess;
};

uniform Material material;
uniform bool enableSpecularMapping;
uniform bool enableNormalMapping;
uniform bool enableParallaxMapping;

uniform bool receiveShadow;
uniform bool enableSplitDisplay;
uniform bool enableShadow;
uniform float transparentDiscardLimit;
uniform bool transparentDiscard;