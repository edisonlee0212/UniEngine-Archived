#extension GL_ARB_bindless_texture : require


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


//Camera
layout (std140, binding = 0) uniform UE_CAMERA
{
	mat4 UE_CAMERA_PROJECTION;
	mat4 UE_CAMERA_VIEW;
	vec4 UE_CAMERA_RESERVED;
	vec3 UE_CAMERA_POSITION;
};

layout (std140, binding = 1) uniform UE_DIRECTIONAL_LIGHT_BLOCK
{
	int UE_DIRECTIONAL_LIGHT_BLOCK_AMOUNT;
	DirectionalLight UE_DIRECTIONAL_LIGHT_BLOCKS[DIRECTIONAL_LIGHTS_AMOUNT];
};

layout (std140, binding = 2) uniform UE_POINT_LIGHT_BLOCK
{
	int UE_POINT_LIGHT_AMOUNT;
	PointLight UE_POINT_LIGHTS[POINT_LIGHTS_AMOUNT];
};

layout (std140, binding = 3) uniform UE_SPOT_LIGHT_BLOCK
{
	int UE_SPOT_LIGHT_AMOUNT;
	SpotLight UE_SPOT_LIGHTS[SPOT_LIGHTS_AMOUNT];
};

layout (std140, binding = 4) uniform UE_LIGHT_SETTINGS_BLOCK
{
	float UE_SHADOW_SPLIT_0;
	float UE_SHADOW_SPLIT_1;
	float UE_SHADOW_SPLIT_2;
	float UE_SHADOW_SPLIT_3;
	int UE_SHADOW_SAMPLE_SIZE;
	float UE_SHADOW_PCSS_DIRECTIONAL_LIGHT_SCALE;
	int UE_SHADOW_PCSS_BLOCKER_SEARCH_SIZE;
	float UE_SHADOW_SEAM_FIX_RATIO;
	float UE_SHADOW_VSM_VARIANCE;
	float UE_SHADOW_LIGHT_BLEED_FACTOR;
	float UE_SHADOW_EVSM_EXP;
	float UE_AMBIENT_LIGHT;
};

layout (std140, binding = 5) uniform UE_KERNEL_BLOCK
{
	vec4 UE_UNIFORM_KERNEL[MAX_KERNEL_AMOUNT];
	vec4 UE_GAUSS_KERNEL[MAX_KERNEL_AMOUNT];
};

layout (std140, binding = 6) uniform UE_MATERIAL_BLOCK
{
	sampler2D UE_SPOT_LIGHT_SM;
	sampler2DArray UE_DIRECTIONAL_LIGHT_SM;
	sampler2DArray UE_POINT_LIGHT_SM;

	sampler2D UE_ALBEDO_MAP;
	sampler2D UE_NORMAL_MAP;
	sampler2D UE_METALLIC_MAP;
	sampler2D UE_ROUGHNESS_MAP;
	sampler2D UE_AO_MAP;
	
	sampler2D UE_AMBIENT_MAP;
	sampler2D UE_DIFFUSE_MAP;
	sampler2D UE_SPECULAR_MAP;
	sampler2D UE_EMISSIVE_MAP;
	sampler2D UE_DISPLACEMENT_MAP;

	bool UE_ALBEDO_MAP_ENABLED;
	bool UE_NORMAL_MAP_ENABLED;
	bool UE_METALLIC_MAP_ENABLED;
	bool UE_ROUGHNESS_MAP_ENABLED;
	bool UE_AO_MAP_ENABLED;
	
	bool UE_AMBIENT_MAP_ENABLED;
	bool UE_DIFFUSE_MAP_ENABLED;
	bool UE_SPECULAR_MAP_ENABLED;
	bool UE_EMISSIVE_MAP_ENABLED;
	bool UE_DISPLACEMENT_MAP_ENABLED;
};

//Material
struct Material{
	float shininess;
};

uniform Material material;


uniform bool receiveShadow;
uniform bool enableSplitDisplay;
uniform bool enableShadow;
uniform float transparentDiscardLimit;
uniform bool transparentDiscard;