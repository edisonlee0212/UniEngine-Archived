layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec3 Tangent;
	vec2 TexCoords;
} fs_in;

uniform float heightScale;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * heightScale; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(TEXTURE_HEIGHT0, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(TEXTURE_HEIGHT0, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(TEXTURE_HEIGHT0, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

void main()
{
	vec3 B = cross(fs_in.Normal, fs_in.Tangent);
	mat3 TBN = mat3(fs_in.Tangent, B, fs_in.Normal);

    vec2 texCoords = fs_in.TexCoords;
    if(enableParallaxMapping){
        texCoords = ParallaxMapping(fs_in.TexCoords, (TBN * CameraPosition - TBN * fs_in.FragPos));
    }

	vec4 albedo = texture(TEXTURE_DIFFUSE0, texCoords).rgba;
	if(albedo.a < 0.5)
        discard;
    // store the fragment position vector in the first gbuffer texture
    gPosition.rgb = fs_in.FragPos;
	gPosition.a = 1.0;

    vec3 normal = fs_in.Normal;
	if(enableNormalMapping){
		normal = texture(TEXTURE_NORMAL0, texCoords).rgb;
		normal = normal * 2.0 - 1.0;   
		normal = normalize(TBN * normal); 
	}
    
    // also store the per-fragment normals into the gbuffer
    gNormal.rgb = (gl_FrontFacing ? 1.0 : -1.0) * normalize(normal);
	gNormal.a = material.shininess;
    // store specular intensity in gAlbedoSpec's alpha component
    float specular = 1.0;
	if(enableSpecularMapping){
		specular = texture(TEXTURE_SPECULAR0, texCoords).r;
	}

	gAlbedoSpec.rgb = albedo.rgb;
	gAlbedoSpec.a = specular;
}