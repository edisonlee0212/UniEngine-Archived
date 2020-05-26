struct Material{
	float shininess;
};

uniform Material material;

uniform sampler2D TEXTURE_DIFFUSE[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_SPECULAR[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_AMBIENT[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_EMISSIVE[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_HEIGHT[MAX_TEXTURES_AMOUNT];
uniform sampler2D TEXTURE_NORMAL[MAX_TEXTURES_AMOUNT];