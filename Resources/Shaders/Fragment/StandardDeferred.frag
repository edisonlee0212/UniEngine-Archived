layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec3 Tangent;
	vec2 TexCoords;
} fs_in;

float heightScale = 0.05;

vec3 ParallaxMapping(vec2 texCoords, vec3 viewDir)
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
    float currentDepthMapValue = texture(UE_HEIGHT_MAP, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(UE_HEIGHT_MAP, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(UE_HEIGHT_MAP, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return vec3(finalTexCoords, currentLayerDepth * 10);
}

void main()
{
	vec3 B = cross(fs_in.Normal, fs_in.Tangent);
	mat3 TBN = mat3(fs_in.Tangent, B, fs_in.Normal);

    vec2 texCoords = fs_in.TexCoords;
    float depth = 0.0;

    if(UE_PARALLAX_MAP_ENABLED){
        vec3 viewDir = reflect(normalize(UE_CAMERA_POSITION - fs_in.FragPos), fs_in.Normal);
        vec3 result = ParallaxMapping(texCoords, normalize(TBN * viewDir));
        depth = result.z / heightScale;
        texCoords = result.xy;
    }

    vec3 normal = fs_in.Normal;
	if(UE_NORMAL_MAP_ENABLED){
		normal = texture(UE_NORMAL_MAP, texCoords).rgb;
		normal = normal * 2.0 - 1.0;   
		normal = normalize(TBN * normal); 
	}

	vec4 albedo = texture(UE_DIFFUSE_MAP, texCoords).rgba;
	if(albedo.a < 0.5)
        discard;
    // store the fragment position vector in the first gbuffer texture
    gPosition.rgb = fs_in.FragPos - (depth * fs_in.Normal);
	gPosition.a = 1.0;

    
    
    // also store the per-fragment normals into the gbuffer
    gNormal.rgb = (gl_FrontFacing ? 1.0 : -1.0) * normalize(normal);
	gNormal.a = material.shininess;
    // store specular intensity in gAlbedoSpec's alpha component
    float specular = 1.0;
	if(UE_SPECULAR_MAP_ENABLED){
		specular = texture(UE_SPECULAR_MAP, texCoords).r;
	}

	gAlbedoSpec.rgb = albedo.rgb;
	gAlbedoSpec.a = specular;
}