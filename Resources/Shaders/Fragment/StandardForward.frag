out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec3 Tangent;
	vec2 TexCoords;
} fs_in;

vec3 CalculateLights(float shininess, vec3 albedo, float specular, float dist, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 CalcDirectionalLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 fragPos, vec3 viewDir);
float DirectionalLightShadowCalculation(int i, int splitIndex, vec3 fragPos, vec3 normal);
float PointLightShadowCalculation(int i, vec3 fragPos, vec3 normal);
float SpotLightShadowCalculation(int i, vec3 fragPos, vec3 normal);
void main()
{	
	vec4 textureColor = texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgba;
	if(transparentDiscard && textureColor.a < transparentDiscardLimit)
        discard;
	float specular = 1.0;
	if(enableSpecularMapping){
		specular = texture(TEXTURE_SPECULAR0, fs_in.TexCoords).r;
	}
	// properties
	vec3 normal = fs_in.Normal;
	if(enableNormalMapping){
		vec3 B = cross(fs_in.Normal, fs_in.Tangent);
		mat3 TBN = mat3(fs_in.Tangent, B, fs_in.Normal);
		normal = texture(TEXTURE_NORMAL0, fs_in.TexCoords).rgb;
		normal = normal * 2.0 - 1.0;   
		normal = normalize(TBN * normal); 
	}
	
	vec3 viewDir = normalize(CameraPosition - fs_in.FragPos);
	float dist = distance(fs_in.FragPos, CameraPosition);

	vec3 result = CalculateLights(material.shininess, textureColor.rgb, specular, dist, normal, viewDir, fs_in.FragPos);
	FragColor = vec4(result + AmbientLight * textureColor.rgb, textureColor.a);
}


vec3 CalculateLights(float shininess, vec3 albedo, float specular, float dist, vec3 normal, vec3 viewDir, vec3 fragPos){
	vec3 result = vec3(0.0, 0.0, 0.0);

	// phase 1: directional lighting
	for(int i = 0; i < DirectionalLightCount; i++){
		float shadow = 1.0;
		if(enableShadow && receiveShadow){
			int split = 0;
			if(dist < SplitDistance0 - SplitDistance0 * SeamFixRatio){
				shadow = DirectionalLightShadowCalculation(i, 0, fragPos, normal);
			}else if(dist < SplitDistance0){
				//Blend between split 1 & 2
				shadow = DirectionalLightShadowCalculation(i, 0, fragPos, normal);
				float nextLevel = DirectionalLightShadowCalculation(i, 1, fragPos, normal);
				shadow = (nextLevel * (dist - (SplitDistance0 - SplitDistance0 * SeamFixRatio)) + shadow * (SplitDistance0 - dist)) / (SplitDistance0 * SeamFixRatio);
			}else if(dist < SplitDistance1 - SplitDistance1 * SeamFixRatio){
				shadow = DirectionalLightShadowCalculation(i, 1, fragPos, normal);
			}else if(dist < SplitDistance1){
				//Blend between split 2 & 3
				shadow = DirectionalLightShadowCalculation(i, 1, fragPos, normal);
				float nextLevel = DirectionalLightShadowCalculation(i, 2, fragPos, normal);
				shadow = (nextLevel * (dist - (SplitDistance1 - SplitDistance1 * SeamFixRatio)) + shadow * (SplitDistance1 - dist)) / (SplitDistance1 * SeamFixRatio);
			}else if(dist < SplitDistance2 - SplitDistance2 * SeamFixRatio){
				shadow = DirectionalLightShadowCalculation(i, 2, fragPos, normal);
			}else if(dist < SplitDistance2){
				//Blend between split 3 & 4
				shadow = DirectionalLightShadowCalculation(i, 2, fragPos, normal);
				float nextLevel = DirectionalLightShadowCalculation(i, 3, fragPos, normal);
				shadow = (nextLevel * (dist - (SplitDistance2 - SplitDistance2 * SeamFixRatio)) + shadow * (SplitDistance2 - dist)) / (SplitDistance2 * SeamFixRatio);
			}else if(dist < SplitDistance3){
				shadow = DirectionalLightShadowCalculation(i, 3, fragPos, normal);
			}else{
				shadow = 1.0;
			}
		}
		result += CalcDirectionalLight(shininess, albedo, specular, i, normal, viewDir) * shadow;
	}
	// phase 2: point lights
	for(int i = 0; i < PointLightCount; i++){
		float shadow = 1.0;
		if(enableShadow && receiveShadow){
			shadow = PointLightShadowCalculation(i, fragPos, normal);
		}
		result += CalcPointLight(shininess, albedo, specular, i, normal, fragPos, viewDir) * shadow;
	}
	// phase 3: spot light
	for(int i = 0; i < SpotLightCount; i++){
		float shadow = 1.0;
		if(enableShadow && receiveShadow){
			shadow = SpotLightShadowCalculation(i, fragPos, normal);
		}
		result += CalcSpotLight(shininess, albedo, specular, i, normal, fragPos, viewDir) * shadow;
	}
	return result;
}

// calculates the color when using a directional light.
vec3 CalcDirectionalLight(float shininess, vec3 albedo, float specular, int i, vec3 normal, vec3 viewDir)
{
	DirectionalLight light = DirectionalLights[i];
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
	PointLight light = PointLights[i];
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
	SpotLight light = SpotLights[i];
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

float DirectionalLightShadowCalculation(int i, int splitIndex, vec3 fragPos, vec3 normal)
{
	DirectionalLight light = DirectionalLights[i];
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

	int sampleAmount = PCSSBSAmount;
	float sampleWidth = lightSize / light.lightFrustumWidth[splitIndex] / sampleAmount;

	float texScale = float(light.viewPortXSize) / float(textureSize(directionalShadowMap, 0).x);
	vec2 texBase = vec2(float(light.viewPortXStart) / float(textureSize(directionalShadowMap, 0).y), float(light.viewPortYStart) / float(textureSize(directionalShadowMap, 0).y));

	
	for(int i = -sampleAmount; i <= sampleAmount; i++)
	{
		for(int j = -sampleAmount; j <= sampleAmount; j++){
			vec2 texCoord = projCoords.xy + vec2(i, j) * sampleWidth;
			float closestDepth = texture(directionalShadowMap, vec3(texCoord * texScale + texBase, splitIndex)).r;
			int tf = int(closestDepth != 0.0 && projCoords.z > closestDepth);
			avgDistance += closestDepth * tf;
			blockers += tf;
		}
	}
	if(blockers == 0) return 1.0;
	float blockerDistance = avgDistance / blockers;
	float penumbraWidth = (projCoords.z - blockerDistance) / blockerDistance * lightSize;
	float texelSize = penumbraWidth * PCSSScaleFactor / DirectionalLights[i].lightFrustumWidth[splitIndex] * DirectionalLights[i].lightFrustumDistance[splitIndex] / 100.0;
	
	int shadowCount = 0;
	sampleAmount = PCSSPCFSampleAmount;
	for(int i = 0; i < sampleAmount; i++)
	{
		//vec2 texCoord = projCoords.xy + UniformKernel[i % MAX_KERNEL_AMOUNT].xy * texelSize;
		vec2 texCoord = projCoords.xy + VogelDiskSample(i, sampleAmount, InterleavedGradientNoise(fragPos * 3141)) * texelSize;
		float closestDepth = texture(directionalShadowMap, vec3(texCoord * texScale + texBase, splitIndex)).r;
		if(closestDepth == 0.0) continue;
		shadow += projCoords.z < closestDepth ? 1.0 : 0.0;
	}
	shadow /= sampleAmount;
	return shadow;
}

float PointLightShadowCalculation(int i, vec3 fragPos, vec3 normal)
{
	PointLight light = PointLights[i];
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
	float texScale = float(light.viewPortXSize) / float(textureSize(pointShadowMap, 0).x);
	vec2 texBase = vec2(float(light.viewPortXStart) / float(textureSize(pointShadowMap, 0).y), float(light.viewPortYStart) / float(textureSize(pointShadowMap, 0).y));

	//Blocker Search
	int sampleAmount = PCSSBSAmount;
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
			float closestDepth = texture(pointShadowMap, vec3(texCoord * texScale + texBase, slice)).r;
			int tf = int(closestDepth != 0.0 && projCoords.z > closestDepth);
			avgDistance += closestDepth * tf;
			blockers += tf;
		}
	}

	if(blockers == 0) return 1.0;
	float blockerDistance = avgDistance / blockers;
	float penumbraWidth = (projCoords.z - blockerDistance) / blockerDistance * lightSize * PCSSScaleFactor;	
	//End search
	sampleAmount = PCSSPCFSampleAmount;
	for(int i = 0; i < sampleAmount; i++)
	{
		vec2 texCoord = projCoords.xy + VogelDiskSample(i, sampleAmount, InterleavedGradientNoise(fragPos * 3141)) * penumbraWidth;
		texCoord.x = clamp(texCoord.x, 1.0 / float(light.viewPortXSize), 1.0 - 1.0 / float(light.viewPortXSize));
		texCoord.y = clamp(texCoord.y, 1.0 / float(light.viewPortXSize), 1.0 - 1.0 / float(light.viewPortXSize));
		float closestDepth = texture(pointShadowMap, vec3(texCoord * texScale + texBase, slice)).r;
		if(closestDepth == 0.0) continue;
		shadow += projCoords.z < closestDepth ? 1.0 : 0.0;
	}
	shadow /= sampleAmount;
	return shadow;
}

float SpotLightShadowCalculation(int i, vec3 fragPos, vec3 normal){
	SpotLight light = SpotLights[i];
	vec3 lightPos = light.position;
	vec3 fragToLight = fragPos - lightPos;
	float shadow = 0.0;
	float bias = light.cutOffOuterCutOffLightSizeBias.w;
	vec4 fragPosLightSpace = light.lightSpaceMatrix * vec4(fragPos, 1.0);
	fragPosLightSpace.z -= bias;
	vec3 projCoords = (fragPosLightSpace.xyz) / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float texScale = float(light.viewPortXSize) / float(textureSize(spotShadowMap, 0).x);
	vec2 texBase = vec2(float(light.viewPortXStart) / float(textureSize(spotShadowMap, 0).y), float(light.viewPortYStart) / float(textureSize(spotShadowMap, 0).y));
	//Blocker Search
	int sampleAmount = PCSSBSAmount;
	float lightSize = light.cutOffOuterCutOffLightSizeBias.z * projCoords.z;
	float blockers = 0;
	float avgDistance = 0;
	float sampleWidth = lightSize / sampleAmount;
	for(int i = -sampleAmount; i <= sampleAmount; i++)
	{
		for(int j = -sampleAmount; j <= sampleAmount; j++){
			vec2 texCoord = projCoords.xy + vec2(i, j) * sampleWidth;
			float closestDepth = texture(spotShadowMap, vec2(texCoord * texScale + texBase)).r;
			int tf = int(closestDepth != 0.0 && projCoords.z > closestDepth);
			avgDistance += closestDepth * tf;
			blockers += tf;
		}
	}
	if(blockers == 0) return 1.0;
	float blockerDistance = avgDistance / blockers;
	float penumbraWidth = (projCoords.z - blockerDistance) / blockerDistance * lightSize * PCSSScaleFactor;	
	//End search
	sampleAmount = PCSSPCFSampleAmount;
	for(int i = 0; i < sampleAmount; i++)
	{
		vec2 texCoord = projCoords.xy + VogelDiskSample(i, sampleAmount, InterleavedGradientNoise(fragPos * 3141)) * penumbraWidth;
		float closestDepth = texture(spotShadowMap, vec2(texCoord * texScale + texBase)).r;
		if(closestDepth == 0.0) continue;
		shadow += projCoords.z < closestDepth ? 1.0 : 0.0;
	}
	shadow /= sampleAmount;
	return shadow;
}