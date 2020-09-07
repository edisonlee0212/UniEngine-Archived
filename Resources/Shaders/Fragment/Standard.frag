out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	mat3 TBN;
	vec2 TexCoords;
} fs_in;

vec3 CalculateLights(float dist, vec3 normal, vec3 viewDir, vec3 fragPos);


vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

float DirectionalLightShadowCalculation(int i, int splitIndex, DirectionalLight light, vec4 fragPosLightSpace, vec3 normal);
float PointLightShadowCalculation(int i, PointLight light, vec3 fragPos, vec3 normal);

void main()
{	
	// properties
	vec3 normal;
	if(enableNormalMapping){
		normal = texture(TEXTURE_NORMAL0, fs_in.TexCoords).rgb;
		normal = normal * 2.0 - 1.0;   
		normal = normalize(fs_in.TBN * normal); 
	}else{
		normal = fs_in.Normal;
	}
	
	vec3 viewDir = normalize(CameraPosition - fs_in.FragPos);
	float dist = distance(fs_in.FragPos, CameraPosition);

	vec3 result = CalculateLights(dist, normal, viewDir, fs_in.FragPos);
	if(DisplaySplit != 0){
		if(dist < SplitDistance0){
			result += vec3(0.0, 0.0, 0.2);
		}else if(dist < SplitDistance1){
			result += vec3(0.2, 0.0, 0.0);
		}else if(dist < SplitDistance2){
			result += vec3(0.0, 0.2, 0.0);
		}else if(dist < SplitDistance3){
		}
	}
	FragColor = vec4(result + AmbientLight * texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgb, texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).a);
}



vec3 CalculateLights(float dist, vec3 normal, vec3 viewDir, vec3 fragPos){
	vec3 norm = normalize(normal);
	vec3 result = vec3(0.0, 0.0, 0.0);

	// phase 1: directional lighting
	for(int i = 0; i < DirectionalLightCount; i++){
		int split = 0;
		float shadow = 0.0;
		if(dist < SplitDistance0 - SplitDistance0 * SeamFixRatio){
			shadow = DirectionalLightShadowCalculation(i, 0, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[0] * vec4(fs_in.FragPos, 1.0), norm);
		}else if(dist < SplitDistance0){
			//Blend between split 1 & 2
			shadow = DirectionalLightShadowCalculation(i, 0, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[0] * vec4(fs_in.FragPos, 1.0), norm);
			float nextLevel = DirectionalLightShadowCalculation(i, 1, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[1] * vec4(fs_in.FragPos, 1.0), norm);
			shadow = (nextLevel * (dist - (SplitDistance0 - SplitDistance0 * SeamFixRatio)) + shadow * (SplitDistance0 - dist)) / (SplitDistance0 * SeamFixRatio);
		}else if(dist < SplitDistance1 - SplitDistance1 * SeamFixRatio){
			shadow = DirectionalLightShadowCalculation(i, 1, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[1] * vec4(fs_in.FragPos, 1.0), norm);
		}else if(dist < SplitDistance1){
			//Blend between split 2 & 3
			shadow = DirectionalLightShadowCalculation(i, 1, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[1] * vec4(fs_in.FragPos, 1.0), norm);
			float nextLevel = DirectionalLightShadowCalculation(i, 2, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[2] * vec4(fs_in.FragPos, 1.0), norm);
			shadow = (nextLevel * (dist - (SplitDistance1 - SplitDistance1 * SeamFixRatio)) + shadow * (SplitDistance1 - dist)) / (SplitDistance1 * SeamFixRatio);
		}else if(dist < SplitDistance2 - SplitDistance2 * SeamFixRatio){
			shadow = DirectionalLightShadowCalculation(i, 2, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[2] * vec4(fs_in.FragPos, 1.0), norm);
		}else if(dist < SplitDistance2){
			//Blend between split 3 & 4
			shadow = DirectionalLightShadowCalculation(i, 2, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[2] * vec4(fs_in.FragPos, 1.0), norm);
			float nextLevel = DirectionalLightShadowCalculation(i, 3, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[3] * vec4(fs_in.FragPos, 1.0), norm);
			shadow = (nextLevel * (dist - (SplitDistance2 - SplitDistance2 * SeamFixRatio)) + shadow * (SplitDistance2 - dist)) / (SplitDistance2 * SeamFixRatio);
		}else if(dist < SplitDistance3){
			shadow = DirectionalLightShadowCalculation(i, 3, DirectionalLights[i], DirectionalLights[i].lightSpaceMatrix[3] * vec4(fs_in.FragPos, 1.0), norm);
		}else{
			shadow = 1.0;
		}
		
		result += CalcDirectionalLight(DirectionalLights[i], norm, viewDir) * (shadow);
	}
	// phase 2: point lights
	for(int i = 0; i < PointLightCount; i++){
		float shadow = PointLightShadowCalculation(i, PointLights[i], fragPos, norm);
		result += CalcPointLight(PointLights[i], norm, fragPos, viewDir) * (1.0 - shadow);
	}
	// phase 3: spot light
	for(int i = 0; i < SpotLightCount; i++){
		result += CalcSpotLight(SpotLights[i], norm, fragPos, viewDir);
	}
	return result;
}

// calculates the color when using a directional light.
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	// combine results
	vec3 diffuse = light.diffuse * diff * texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgb;
	vec3 specular = light.specular * spec;
	if(enableSpecularMapping){
		specular *= texture(TEXTURE_SPECULAR0, fs_in.TexCoords).r;
	}else{
		specular *= texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgb;
	}
	return (diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constantLinearQuadFarPlane.x + light.constantLinearQuadFarPlane.y * distance + light.constantLinearQuadFarPlane.z * (distance * distance));	
	// combine results
	vec3 diffuse = light.diffuse * diff * texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgb;
	vec3 specular = light.specular * spec;
	if(enableSpecularMapping){
		specular *= texture(TEXTURE_SPECULAR0, fs_in.TexCoords).r;
	}else{
		specular *= texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgb;
	}
	diffuse *= attenuation;
	specular *= attenuation;
	return (diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));	
	// spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// combine results
	vec3 diffuse = light.diffuse * diff * texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgb;
	vec3 specular = light.specular * spec;
	if(enableSpecularMapping){
		specular *= texture(TEXTURE_SPECULAR0, fs_in.TexCoords).r;
	}else{
		specular *= texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgb;
	}
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return (diffuse + specular);
}



// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float Linstep(float minVal, float maxVal, float val) {
	return clamp((val - minVal) / (maxVal - minVal), 0.0, 1.0);
}
float ReduceLightBleed(float p_max, float amount) {
	return Linstep(amount, 1.0, p_max);
}

float Chebyshev(vec2 moments, float depth)
{
	if (depth <= moments.x) {
		return 1.0;
	}

	float variance = moments.y - (moments.x * moments.x);
	variance = max(variance, VSMMaxVariance / 1000.0);

	float d = depth - moments.x; // attenuation
	float p_max = variance / (variance + d * d);

	return ReduceLightBleed(p_max, LightBleedFactor);
}

float kernel7[49] = {
0.000036, 0.000363, 0.001446, 0.002291, 0.001446, 0.000363, 0.000036,
0.000363, 0.003676, 0.014662, 0.023226, 0.014662, 0.003676, 0.000363,
0.001446, 0.014662, 0.058488, 0.092651, 0.058488, 0.014662, 0.001446,
0.002291, 0.023226, 0.092651, 0.146768, 0.092651, 0.023226, 0.002291,
0.001446, 0.014662, 0.058488, 0.092651, 0.058488, 0.014662, 0.001446,
0.000363, 0.003676, 0.014662, 0.023226, 0.014662, 0.003676, 0.000363,
0.000036, 0.000363, 0.001446, 0.002291, 0.001446, 0.000363, 0.000036
};
vec2 poissonDisk[16] = {
 vec2( -0.94201624, -0.39906216 ),
 vec2( 0.94558609, -0.76890725 ),
 vec2( -0.094184101, -0.92938870 ),
 vec2( 0.34495938, 0.29387760 ),
 vec2( -0.91588581, 0.45771432 ),
 vec2( -0.81544232, -0.87912464 ),
 vec2( -0.38277543, 0.27676845 ),
 vec2( 0.97484398, 0.75648379 ),
 vec2( 0.44323325, -0.97511554 ),
 vec2( 0.53742981, -0.47373420 ),
 vec2( -0.26496911, -0.41893023 ),
 vec2( 0.79197514, 0.19090188 ),
 vec2( -0.24188840, 0.99706507 ),
 vec2( -0.81409955, 0.91437590 ),
 vec2( 0.19984126, 0.78641367 ),
 vec2( 0.14383161, -0.14100790 )
};
float DirectionalLightBlockerSearch(int index, vec3 shadowCoords, float searchWidth, int sampleAmount){
	int blockers = 0;
	float avgDistance = 0;
	float step = searchWidth / sampleAmount / DirectionalLights[index / 4].lightFrustumWidth[index % 4];
	for(int x = -sampleAmount; x < sampleAmount; x++){
		for(int y = -sampleAmount; y < sampleAmount; y++){
			float closestDepth = texture(directionalShadowMap, vec3(shadowCoords.xy + vec2(x, y) * step, index)).r;
			if(closestDepth != 0.0 && shadowCoords.z > closestDepth){
				avgDistance += closestDepth ;
				blockers++;
			}
		}
	}
	if(blockers == 0) return 0.0;
	return (avgDistance / blockers);
}


float DirectionalLightShadowCalculation(int i, int splitIndex, DirectionalLight light, vec4 fragPosLightSpace, vec3 normal)
{
	vec3 lightDir = light.direction;
	float bias = light.ReservedParameters.z;
	float normalOffset = light.ReservedParameters.w;
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
	float blockerDistance = DirectionalLightBlockerSearch(i * 4 + splitIndex, projCoords, lightSize, 3);
	if(blockerDistance < 0.1) return 1.0;
	float penumbraWidth = (projCoords.z - blockerDistance) / blockerDistance * lightSize;
	int sampleWidth = 10;
	float texelSize = penumbraWidth / sampleWidth * PCSSScaleFactor / DirectionalLights[i].lightFrustumWidth[splitIndex] * DirectionalLights[i].lightFrustumDistance[splitIndex] / 100;
	int sampleAmount = 0;
	
	for(int x = -sampleWidth; x <= sampleWidth; ++x)
	{
		for(int y = -sampleWidth; y <= sampleWidth; ++y)
		{
			float cloestDepth = texture(directionalShadowMap, vec3(projCoords.xy + vec2(x, y) * texelSize, i * 4 + splitIndex)).r;
			if(cloestDepth == 0.0) continue;
			shadow += projCoords.z < cloestDepth ? 1.0 : 0.0;
			sampleAmount++;
		}
	}
	if(sampleAmount == 0) return 1.0;
	shadow /= sampleAmount;
	return shadow;
}

float PointLightShadowCalculation(int i, PointLight light, vec3 fragPos, vec3 normal)
{
	vec3 viewPos = CameraPosition;
	vec3 lightPos = light.position;
	float far_plane = light.constantLinearQuadFarPlane.w;
	// get vector between fragment position and light position
	vec3 fragToLight = fragPos - lightPos;
	float currentDepth = length(fragToLight);
	if(currentDepth > far_plane) return 0.0;
	float shadow = 0.0;
	float bias = light.ReservedParameters.x;
	int samples = 20;
	float viewDistance = length(viewPos - fragPos);
	float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
	float compare = 0.0;
	for(int j = 0; j < samples; ++j)
	{
		shadow += texture(pointShadowMap, vec4((fragToLight + gridSamplingDisk[j] * diskRadius), i), (currentDepth - bias) / far_plane, 0);
	}
	shadow /= float(samples);
	return shadow;
}
