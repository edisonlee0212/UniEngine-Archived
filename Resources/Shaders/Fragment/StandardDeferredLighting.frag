out vec4 FragColor;

in VS_OUT {
	vec2 TexCoords;
} fs_in;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform bool enableSSAO;
uniform sampler2D ssao;

vec3 CalculateLights(float shininess, vec3 albedo, float specular, float dist, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 CalcDirectionalLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir);
float UE_DIRECTIONAL_LIGHT_BLOCKShadowCalculation(int i, int splitIndex, vec3 fragPos, vec3 normal);
float UE_POINT_LIGHTShadowCalculation(int i, vec3 fragPos, vec3 normal);
float UE_SPOT_LIGHTShadowCalculation(int i, vec3 fragPos, vec3 normal);
void main()
{	
	vec3 fragPos = texture(gPosition, fs_in.TexCoords).rgb;
	vec3 normal = texture(gNormal, fs_in.TexCoords).rgb;
	float shininess = texture(gNormal, fs_in.TexCoords).a;
	vec3 albedo = texture(gAlbedoSpec, fs_in.TexCoords).rgb;
	float specular = texture(gAlbedoSpec, fs_in.TexCoords).a;
	vec3 viewDir = normalize(UE_CAMERA_POSITION - fragPos);
	float dist = distance(fragPos, UE_CAMERA_POSITION);

	float AmbientOcclusion = (enableSSAO ? texture(ssao, fs_in.TexCoords).r : 1.0);

	vec3 result = CalculateLights(shininess, albedo, specular, dist, normal, viewDir, fragPos);
	FragColor = vec4(result * AmbientOcclusion + UE_AMBIENT_LIGHT * albedo * AmbientOcclusion, 1.0);
}


vec3 CalculateLights(float shininess, vec3 albedo, float specular, float dist, vec3 normal, vec3 viewDir, vec3 fragPos){
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
		result += CalcDirectionalLight(shininess, albedo, specular, i, normal, viewDir) * shadow;
	}
	// phase 2: point lights
	for(int i = 0; i < UE_POINT_LIGHT_AMOUNT; i++){
		float shadow = 1.0;
		if(enableShadow && receiveShadow){
			shadow = UE_POINT_LIGHTShadowCalculation(i, fragPos, normal);
		}
		result += CalcPointLight(shininess, albedo, specular, i, normal, fragPos, viewDir) * shadow;
	}
	// phase 3: spot light
	for(int i = 0; i < UE_SPOT_LIGHT_AMOUNT; i++){
		float shadow = 1.0;
		if(enableShadow && receiveShadow){
			shadow = UE_SPOT_LIGHTShadowCalculation(i, fragPos, normal);
		}
		result += CalcSpotLight(shininess, albedo, specular, i, normal, fragPos, viewDir) * shadow;
	}
	return result;
}

// calculates the color when using a directional light.
vec3 CalcDirectionalLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 viewDir)
{
	DirectionalLight light = UE_DIRECTIONAL_LIGHT_BLOCKS[i];
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
	// combine results
	vec3 diffuseOutput = light.diffuse * diff * albedo;
	vec3 specularOutput = light.specular * spec * albedo * specular;
	return (diffuseOutput + specularOutput);
}

// calculates the color when using a point light.
vec3 CalcPointLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	PointLight light = UE_POINT_LIGHTS[i];
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constantLinearQuadFarPlane.x + light.constantLinearQuadFarPlane.y * distance + light.constantLinearQuadFarPlane.z * (distance * distance));	
	// combine results
	vec3 diffuseOutput = light.diffuse * diff * albedo;
	vec3 specularOutput = light.specular * spec * albedo * specular;
	diffuseOutput *= attenuation;
	specularOutput *= attenuation;
	return (diffuseOutput + specularOutput);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	SpotLight light = UE_SPOT_LIGHTS[i];
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constantLinearQuadFarPlane.x + light.constantLinearQuadFarPlane.y * distance + light.constantLinearQuadFarPlane.z * (distance * distance));	
	// spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon = light.cutOffOuterCutOffLightSizeBias.x - light.cutOffOuterCutOffLightSizeBias.y;
	float intensity = clamp((theta - light.cutOffOuterCutOffLightSizeBias.y) / epsilon, 0.0, 1.0);
	// combine results
	vec3 diffuseOutput = light.diffuse * diff * albedo;
	vec3 specularOutput = light.specular * spec * albedo * specular;
	diffuseOutput *= attenuation * intensity;
	specularOutput *= attenuation * intensity;
	return (diffuseOutput + specularOutput);
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