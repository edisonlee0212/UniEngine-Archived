out vec4 FragColor;

in VS_OUT {
	vec2 TexCoords;
} fs_in;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D gMetallicRoughnessAO;

uniform bool enableSSAO;
uniform sampler2D ssao;

vec3 CalculateLights(float shininess, vec3 albedo, float specular, float dist, vec3 normal, vec3 viewDir, vec3 fragPos, float metallic, float roughness, vec3 F0);
vec3 CalcDirectionalLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 viewDir, float metallic, float roughness, vec3 F0);
vec3 CalcPointLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir, float metallic, float roughness, vec3 F0);
vec3 CalcSpotLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir, float metallic, float roughness, vec3 F0);
float UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(int i, int splitIndex, vec3 fragPos, vec3 normal);
float UE_POINT_LIGHTShadowCalculation(int i, vec3 fragPos, vec3 normal);
float UE_SPOT_LIGHTShadowCalculation(int i, vec3 fragPos, vec3 normal);

const float PI = 3.14159265359;


void main()
{	
	vec3 fragPos = texture(gPosition, fs_in.TexCoords).rgb;

	vec3 albedo = texture(gAlbedoSpec, fs_in.TexCoords).rgb;
	vec3 normal = texture(gNormal, fs_in.TexCoords).rgb;
	float metallic = texture(gMetallicRoughnessAO, fs_in.TexCoords).r;
	float roughness = texture(gMetallicRoughnessAO, fs_in.TexCoords).g;
	float ao = texture(gMetallicRoughnessAO, fs_in.TexCoords).b;

	float shininess = texture(gNormal, fs_in.TexCoords).a;
	float specular = texture(gAlbedoSpec, fs_in.TexCoords).a;
	vec3 viewDir = normalize(UE_CAMERA_POSITION - fragPos);
	float dist = distance(fragPos, UE_CAMERA_POSITION);
	float AmbientOcclusion = (enableSSAO ? texture(ssao, fs_in.TexCoords).r : 1.0);

	// calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
	// of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
	vec3 F0 = vec3(0.04); 
	F0 = mix(F0, albedo, metallic);

	vec3 result = CalculateLights(shininess, albedo, specular, dist, normal, viewDir, fragPos, metallic, roughness, F0);
	vec3 color = (result + UE_AMBIENT_LIGHT * albedo * ao) * AmbientOcclusion;

	// HDR tonemapping
	//color = color / (color + vec3(1.0));
	// gamma correct
	//color = pow(color, vec3(1.0/2.2)); 

	FragColor = vec4(color, 1.0);
}

// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness*roughness;
	float a2 = a*a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH*NdotH;

	float nom   = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom / max(denom, 0.001); // prevent divide by zero for roughness=0.0 and NdotH=1.0
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;

	float nom   = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}


vec3 CalculateLights(float shininess, vec3 albedo, float specular, float dist, vec3 normal, vec3 viewDir, vec3 fragPos, float metallic, float roughness, vec3 F0){
	vec3 result = vec3(0.0, 0.0, 0.0);

	// phase 1: directional lighting
	for(int i = 0; i < UE_DIRECTIONAL_LIGHT_BLOCK_AMOUNT; i++){
		float shadow = 1.0;
		if(enableShadow && receiveShadow){
			int split = 0;
			if(dist < UE_SHADOW_SPLIT_0 - UE_SHADOW_SPLIT_0 * UE_SHADOW_SEAM_FIX_RATIO){
				shadow = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 0, fragPos, normal);
			}else if(dist < UE_SHADOW_SPLIT_0){
				//Blend between split 1 & 2
				shadow = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 0, fragPos, normal);
				float nextLevel = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 1, fragPos, normal);
				shadow = (nextLevel * (dist - (UE_SHADOW_SPLIT_0 - UE_SHADOW_SPLIT_0 * UE_SHADOW_SEAM_FIX_RATIO)) + shadow * (UE_SHADOW_SPLIT_0 - dist)) / (UE_SHADOW_SPLIT_0 * UE_SHADOW_SEAM_FIX_RATIO);
			}else if(dist < UE_SHADOW_SPLIT_1 - UE_SHADOW_SPLIT_1 * UE_SHADOW_SEAM_FIX_RATIO){
				shadow = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 1, fragPos, normal);
			}else if(dist < UE_SHADOW_SPLIT_1){
				//Blend between split 2 & 3
				shadow = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 1, fragPos, normal);
				float nextLevel = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 2, fragPos, normal);
				shadow = (nextLevel * (dist - (UE_SHADOW_SPLIT_1 - UE_SHADOW_SPLIT_1 * UE_SHADOW_SEAM_FIX_RATIO)) + shadow * (UE_SHADOW_SPLIT_1 - dist)) / (UE_SHADOW_SPLIT_1 * UE_SHADOW_SEAM_FIX_RATIO);
			}else if(dist < UE_SHADOW_SPLIT_2 - UE_SHADOW_SPLIT_2 * UE_SHADOW_SEAM_FIX_RATIO){
				shadow = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 2, fragPos, normal);
			}else if(dist < UE_SHADOW_SPLIT_2){
				//Blend between split 3 & 4
				shadow = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 2, fragPos, normal);
				float nextLevel = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 3, fragPos, normal);
				shadow = (nextLevel * (dist - (UE_SHADOW_SPLIT_2 - UE_SHADOW_SPLIT_2 * UE_SHADOW_SEAM_FIX_RATIO)) + shadow * (UE_SHADOW_SPLIT_2 - dist)) / (UE_SHADOW_SPLIT_2 * UE_SHADOW_SEAM_FIX_RATIO);
			}else if(dist < UE_SHADOW_SPLIT_3){
				shadow = UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(i, 3, fragPos, normal);
			}else{
				shadow = 1.0;
			}
		}
		result += CalcDirectionalLight(shininess, albedo, specular, i, normal, viewDir, metallic, roughness, F0) * shadow;
	}
	// phase 2: point lights
	for(int i = 0; i < UE_POINT_LIGHT_AMOUNT; i++){
		float shadow = 1.0;
		if(enableShadow && receiveShadow){
			shadow = UE_POINT_LIGHTShadowCalculation(i, fragPos, normal);
		}
		result += CalcPointLight(shininess, albedo, specular, i, normal, fragPos, viewDir, metallic, roughness, F0) * shadow;
	}
	// phase 3: spot light
	for(int i = 0; i < UE_SPOT_LIGHT_AMOUNT; i++){
		float shadow = 1.0;
		if(enableShadow && receiveShadow){
			shadow = UE_SPOT_LIGHTShadowCalculation(i, fragPos, normal);
		}
		result += CalcSpotLight(shininess, albedo, specular, i, normal, fragPos, viewDir, metallic, roughness, F0) * shadow;
	}
	return result;
}

// calculates the color when using a directional light.
vec3 CalcDirectionalLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 viewDir, float metallic, float roughness, vec3 F0)
{
	DirectionalLight light = UE_DIRECTIONAL_LIGHT_BLOCKS[i];
	vec3 lightDir = normalize(-light.direction);
	vec3 H = normalize(viewDir + lightDir);
	vec3 radiance = light.diffuse;
	float normalDF = DistributionGGX(normal, H, roughness);   
	float G   = GeometrySmith(normal, viewDir, lightDir, roughness);      
	vec3 F    = fresnelSchlick(clamp(dot(H, viewDir), 0.0, 1.0), F0);
	vec3 nominator    = normalDF * G * F; 
	float denominator = 4 * max(dot(normal, viewDir), 0.0) * max(dot(normal, lightDir), 0.0);
	vec3 spec = nominator / max(denominator, 0.001) * specular;
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;	  
	float normaldotlightDir = max(dot(normal, lightDir), 0.0);       
	return (kD * albedo / PI + spec) * radiance * normaldotlightDir;
}

// calculates the color when using a point light.
vec3 CalcPointLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir, float metallic, float roughness, vec3 F0)
{
	PointLight light = UE_POINT_LIGHTS[i];
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 H = normalize(viewDir + lightDir);
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constantLinearQuadFarPlane.x + light.constantLinearQuadFarPlane.y * distance + light.constantLinearQuadFarPlane.z * (distance * distance));	
	vec3 radiance = light.diffuse * attenuation;
	float normalDF = DistributionGGX(normal, H, roughness);   
	float G   = GeometrySmith(normal, viewDir, lightDir, roughness);      
	vec3 F    = fresnelSchlick(clamp(dot(H, viewDir), 0.0, 1.0), F0);
	vec3 nominator    = normalDF * G * F; 
	float denominator = 4 * max(dot(normal, viewDir), 0.0) * max(dot(normal, lightDir), 0.0);
	vec3 spec = nominator / max(denominator, 0.001) * specular;
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;	  
	float normaldotlightDir = max(dot(normal, lightDir), 0.0);       
	return (kD * albedo / PI + spec) * radiance * normaldotlightDir;

}

// calculates the color when using a spot light.
vec3 CalcSpotLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir, float metallic, float roughness, vec3 F0)
{
	SpotLight light = UE_SPOT_LIGHTS[i];
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 H = normalize(viewDir + lightDir);
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constantLinearQuadFarPlane.x + light.constantLinearQuadFarPlane.y * distance + light.constantLinearQuadFarPlane.z * (distance * distance));	
	// spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon = light.cutOffOuterCutOffLightSizeBias.x - light.cutOffOuterCutOffLightSizeBias.y;
	float intensity = clamp((theta - light.cutOffOuterCutOffLightSizeBias.y) / epsilon, 0.0, 1.0);
	
	vec3 radiance = light.diffuse * attenuation * intensity;
	float normalDF = DistributionGGX(normal, H, roughness);   
	float G   = GeometrySmith(normal, viewDir, lightDir, roughness);      
	vec3 F    = fresnelSchlick(clamp(dot(H, viewDir), 0.0, 1.0), F0);
	vec3 nominator    = normalDF * G * F; 
	float denominator = 4 * max(dot(normal, viewDir), 0.0) * max(dot(normal, lightDir), 0.0);
	vec3 spec = nominator / max(denominator, 0.001) * specular;
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;	  
	float normaldotlightDir = max(dot(normal, lightDir), 0.0);       
	return (kD * albedo / PI + spec) * radiance * normaldotlightDir;
}

vec2 VogelDiskSample(int sampleIndex, int sampleCount, float phi)
{
	float goldenAngle = 2.4;
	float r = sqrt(sampleIndex + 0.5) / sqrt(sampleCount);
	float theta = goldenAngle * sampleIndex + phi;
	return r * vec2(cos(theta), sin(theta));
}

float InterleavedGradientNoise(vec3 fragCoords){
	vec3 magic = vec3(0.06711056, 0.00583715, 52.9829189);
	return fract(dot(fragCoords, magic));
}

float UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(int i, int splitIndex, vec3 fragPos, vec3 normal)
{
	DirectionalLight light = UE_DIRECTIONAL_LIGHT_BLOCKS[i];
	vec3 lightDir = light.direction;
	if(dot(lightDir, normal) > -0.02) return 1.0;
	vec4 fragPosLightSpace = light.lightSpaceMatrix[splitIndex] * vec4(fragPos, 1.0);
	float bias = light.ReservedParameters.z * light.lightFrustumWidth[splitIndex] / light.viewPortXSize;
	float normalOffset = light.ReservedParameters.w * light.lightFrustumWidth[splitIndex] / light.viewPortXSize;
	// perform perspective divide
	vec3 projCoords = (fragPosLightSpace.xyz + normal * normalOffset) / fragPosLightSpace.w;
	//
	if(projCoords.z > 1.0){
		return 0.0;
	}
	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;
	// get depth of current fragment from light's perspective
	projCoords = vec3(projCoords.xy, projCoords.z - bias);
	float shadow = 0.0;
	float lightSize = light.ReservedParameters.x;
	

	int blockers = 0;
	float avgDistance = 0;

	int sampleAmount = UE_SHADOW_PCSS_BLOCKER_SEARCH_SIZE;
	float sampleWidth = lightSize / light.lightFrustumWidth[splitIndex] / sampleAmount;

	float texScale = float(light.viewPortXSize) / float(textureSize(UE_DIRECTIONAL_LIGHT_SM, 0).x);
	vec2 texBase = vec2(float(light.viewPortXStart) / float(textureSize(UE_DIRECTIONAL_LIGHT_SM, 0).y), float(light.viewPortYStart) / float(textureSize(UE_DIRECTIONAL_LIGHT_SM, 0).y));

	
	for(int i = -sampleAmount; i <= sampleAmount; i++)
	{
		for(int j = -sampleAmount; j <= sampleAmount; j++){
			vec2 texCoord = projCoords.xy + vec2(i, j) * sampleWidth;
			float closestDepth = texture(UE_DIRECTIONAL_LIGHT_SM, vec3(texCoord * texScale + texBase, splitIndex)).r;
			int tf = int(closestDepth != 0.0 && projCoords.z > closestDepth);
			avgDistance += closestDepth * tf;
			blockers += tf;
		}
	}
	if(blockers == 0) return 1.0;
	float blockerDistance = avgDistance / blockers;
	float penumbraWidth = (projCoords.z - blockerDistance) / blockerDistance * lightSize;
	float texelSize = penumbraWidth * UE_SHADOW_PCSS_DIRECTIONAL_LIGHT_SCALE / UE_DIRECTIONAL_LIGHT_BLOCKS[i].lightFrustumWidth[splitIndex] * UE_DIRECTIONAL_LIGHT_BLOCKS[i].lightFrustumDistance[splitIndex] / 100.0;
	
	int shadowCount = 0;
	sampleAmount = UE_SHADOW_SAMPLE_SIZE;
	for(int i = 0; i < sampleAmount; i++)
	{
		vec2 texCoord = projCoords.xy + VogelDiskSample(i, sampleAmount, InterleavedGradientNoise(fragPos * 3141)) * texelSize;
		float closestDepth = texture(UE_DIRECTIONAL_LIGHT_SM, vec3(texCoord * texScale + texBase, splitIndex)).r;
		if(closestDepth == 0.0) continue;
		shadow += projCoords.z < closestDepth ? 1.0 : 0.0;
	}
	shadow /= sampleAmount;
	return shadow;
}

float UE_POINT_LIGHTShadowCalculation(int i, vec3 fragPos, vec3 normal)
{
	PointLight light = UE_POINT_LIGHTS[i];
	vec3 lightPos = light.position;
	// get vector between fragment position and light position
	vec3 fragToLight = fragPos - lightPos;
	float shadow = 0.0;
	float bias = light.ReservedParameters.x;
	vec3 direction = normalize(fragToLight);
	int slice = 0;
	if (abs(direction.x) >= abs(direction.y) && abs(direction.x) >= abs(direction.z))
	{
		if(direction.x > 0){
			slice = 0;
		}else{
			slice = 1;
		}
	}else if(abs(direction.y) >= abs(direction.z)){
		if(direction.y > 0){
			slice = 2;
		}else{
			slice = 3;
		}
	}else{
		if(direction.z > 0){
			slice = 4;
		}else{
			slice = 5;
		}
	}
	vec4 fragPosLightSpace = light.lightSpaceMatrix[slice] * vec4(fragPos, 1.0);
	fragPosLightSpace.z -= bias;
	vec3 projCoords = (fragPosLightSpace.xyz) / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float texScale = float(light.viewPortXSize) / float(textureSize(UE_POINT_LIGHT_SM, 0).x);
	vec2 texBase = vec2(float(light.viewPortXStart) / float(textureSize(UE_POINT_LIGHT_SM, 0).y), float(light.viewPortYStart) / float(textureSize(UE_POINT_LIGHT_SM, 0).y));

	//Blocker Search
	int sampleAmount = UE_SHADOW_PCSS_BLOCKER_SEARCH_SIZE;
	float lightSize = light.ReservedParameters.y * projCoords.z;
	float blockers = 0;
	float avgDistance = 0;
	float sampleWidth = lightSize / sampleAmount;
	for(int i = -sampleAmount; i <= sampleAmount; i++)
	{
		for(int j = -sampleAmount; j <= sampleAmount; j++){
			vec2 texCoord = projCoords.xy + vec2(i, j) * sampleWidth;
			texCoord.x = clamp(texCoord.x, 1.0 / float(light.viewPortXSize), 1.0 - 1.0 / float(light.viewPortXSize));
			texCoord.y = clamp(texCoord.y, 1.0 / float(light.viewPortXSize), 1.0 - 1.0 / float(light.viewPortXSize));
			float closestDepth = texture(UE_POINT_LIGHT_SM, vec3(texCoord * texScale + texBase, slice)).r;
			int tf = int(closestDepth != 0.0 && projCoords.z > closestDepth);
			avgDistance += closestDepth * tf;
			blockers += tf;
		}
	}

	if(blockers == 0) return 1.0;
	float blockerDistance = avgDistance / blockers;
	float penumbraWidth = (projCoords.z - blockerDistance) / blockerDistance * lightSize * UE_SHADOW_PCSS_DIRECTIONAL_LIGHT_SCALE;	
	//End search
	sampleAmount = UE_SHADOW_SAMPLE_SIZE;
	for(int i = 0; i < sampleAmount; i++)
	{
		vec2 texCoord = projCoords.xy + VogelDiskSample(i, sampleAmount, InterleavedGradientNoise(fragPos * 3141)) * penumbraWidth;
		texCoord.x = clamp(texCoord.x, 1.0 / float(light.viewPortXSize), 1.0 - 1.0 / float(light.viewPortXSize));
		texCoord.y = clamp(texCoord.y, 1.0 / float(light.viewPortXSize), 1.0 - 1.0 / float(light.viewPortXSize));
		float closestDepth = texture(UE_POINT_LIGHT_SM, vec3(texCoord * texScale + texBase, slice)).r;
		if(closestDepth == 0.0) continue;
		shadow += projCoords.z < closestDepth ? 1.0 : 0.0;
	}
	shadow /= sampleAmount;
	return shadow;
}

float UE_SPOT_LIGHTShadowCalculation(int i, vec3 fragPos, vec3 normal){
	SpotLight light = UE_SPOT_LIGHTS[i];
	float bias = light.cutOffOuterCutOffLightSizeBias.w;
	vec4 fragPosLightSpace = light.lightSpaceMatrix * vec4(fragPos, 1.0);
	fragPosLightSpace.z -= bias;
	vec3 projCoords = (fragPosLightSpace.xyz) / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float texScale = float(light.viewPortXSize) / float(textureSize(UE_SPOT_LIGHT_SM, 0).x);
	vec2 texBase = vec2(float(light.viewPortXStart) / float(textureSize(UE_SPOT_LIGHT_SM, 0).y), float(light.viewPortYStart) / float(textureSize(UE_SPOT_LIGHT_SM, 0).y));

	//Blocker Search
	int sampleAmount = UE_SHADOW_PCSS_BLOCKER_SEARCH_SIZE;
	float lightSize = light.cutOffOuterCutOffLightSizeBias.z * projCoords.z / light.cutOffOuterCutOffLightSizeBias.y;
	float blockers = 0;
	float avgDistance = 0;
	float sampleWidth = lightSize / sampleAmount;
	for(int i = -sampleAmount; i <= sampleAmount; i++)
	{
		for(int j = -sampleAmount; j <= sampleAmount; j++){
			vec2 texCoord = projCoords.xy + vec2(i, j) * sampleWidth;
			float closestDepth = texture(UE_SPOT_LIGHT_SM, vec2(texCoord * texScale + texBase)).r;
			int tf = int(closestDepth != 0.0 && projCoords.z > closestDepth);
			avgDistance += closestDepth * tf;
			blockers += tf;
		}
	}
	if(blockers == 0) return 1.0;
	float blockerDistance = avgDistance / blockers;
	float penumbraWidth = (projCoords.z - blockerDistance) / blockerDistance * lightSize * UE_SHADOW_PCSS_DIRECTIONAL_LIGHT_SCALE;	
	//End search
	sampleAmount = UE_SHADOW_SAMPLE_SIZE;
	float shadow = 0.0;
	for(int i = 0; i < sampleAmount; i++)
	{
		vec2 texCoord = projCoords.xy + VogelDiskSample(i, sampleAmount, InterleavedGradientNoise(fragPos * 3141)) * penumbraWidth;
		float closestDepth = texture(UE_SPOT_LIGHT_SM, vec2(texCoord * texScale + texBase)).r;
		if(closestDepth == 0.0) continue;
		shadow += projCoords.z < closestDepth ? 1.0 : 0.0;
	}
	shadow /= sampleAmount;
	return shadow;
}