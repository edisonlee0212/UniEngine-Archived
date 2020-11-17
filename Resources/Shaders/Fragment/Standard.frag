out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec3 Tangent;
	vec2 TexCoords;
} fs_in;

vec3 CalculateLights(float shininess, vec3 albedo, float specular, float dist, vec3 normal, vec3 viewDir, vec3 fragPos);


vec3 CalcDirectionalLight(float shininess, vec3 albedo, float specular, DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(float shininess, vec3 albedo, float specular, PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(float shininess, vec3 albedo, float specular, SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

float DirectionalLightShadowCalculation(int i, int splitIndex, DirectionalLight light, vec3 fragPos, vec3 normal);
float PointLightShadowCalculation(int i, PointLight light, vec3 fragPos, vec3 normal);

void main()
{	
	vec4 textureColor = texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgba;
	if(textureColor.a < 0.1)
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
				shadow = DirectionalLightShadowCalculation(i, 0, DirectionalLights[i], fragPos, normal);
			}else if(dist < SplitDistance0){
				//Blend between split 1 & 2
				shadow = DirectionalLightShadowCalculation(i, 0, DirectionalLights[i], fragPos, normal);
				float nextLevel = DirectionalLightShadowCalculation(i, 1, DirectionalLights[i], fragPos, normal);
				shadow = (nextLevel * (dist - (SplitDistance0 - SplitDistance0 * SeamFixRatio)) + shadow * (SplitDistance0 - dist)) / (SplitDistance0 * SeamFixRatio);
			}else if(dist < SplitDistance1 - SplitDistance1 * SeamFixRatio){
				shadow = DirectionalLightShadowCalculation(i, 1, DirectionalLights[i], fragPos, normal);
			}else if(dist < SplitDistance1){
				//Blend between split 2 & 3
				shadow = DirectionalLightShadowCalculation(i, 1, DirectionalLights[i], fragPos, normal);
				float nextLevel = DirectionalLightShadowCalculation(i, 2, DirectionalLights[i], fragPos, normal);
				shadow = (nextLevel * (dist - (SplitDistance1 - SplitDistance1 * SeamFixRatio)) + shadow * (SplitDistance1 - dist)) / (SplitDistance1 * SeamFixRatio);
			}else if(dist < SplitDistance2 - SplitDistance2 * SeamFixRatio){
				shadow = DirectionalLightShadowCalculation(i, 2, DirectionalLights[i], fragPos, normal);
			}else if(dist < SplitDistance2){
				//Blend between split 3 & 4
				shadow = DirectionalLightShadowCalculation(i, 2, DirectionalLights[i], fragPos, normal);
				float nextLevel = DirectionalLightShadowCalculation(i, 3, DirectionalLights[i], fragPos, normal);
				shadow = (nextLevel * (dist - (SplitDistance2 - SplitDistance2 * SeamFixRatio)) + shadow * (SplitDistance2 - dist)) / (SplitDistance2 * SeamFixRatio);
			}else if(dist < SplitDistance3){
				shadow = DirectionalLightShadowCalculation(i, 3, DirectionalLights[i], fragPos, normal);
			}else{
				shadow = 1.0;
			}
		}
		result += CalcDirectionalLight(shininess, albedo, specular, DirectionalLights[i], normal, viewDir) * shadow;
	}
	// phase 2: point lights
	for(int i = 0; i < PointLightCount; i++){
		float shadow = 0.0;
		if(enableShadow && receiveShadow){
			shadow = PointLightShadowCalculation(i, PointLights[i], fragPos, normal);
		}
		result += CalcPointLight(shininess, albedo, specular, PointLights[i], normal, fragPos, viewDir) * (1.0 - shadow);
	}
	// phase 3: spot light
	for(int i = 0; i < SpotLightCount; i++){
		result += CalcSpotLight(shininess, albedo, specular, SpotLights[i], normal, fragPos, viewDir);
	}
	return result;
}

// calculates the color when using a directional light.
vec3 CalcDirectionalLight(float shininess, vec3 albedo, float specular, DirectionalLight light, vec3 normal, vec3 viewDir)
{
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
vec3 CalcPointLight(float shininess, vec3 albedo, float specular, PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
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
vec3 CalcSpotLight(float shininess, vec3 albedo, float specular, SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));	
	// spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// combine results
	vec3 diffuseOutput = light.diffuse * diff * albedo;
	vec3 specularOutput = light.specular * spec * albedo * specular;
	diffuseOutput *= attenuation * intensity;
	specularOutput *= attenuation * intensity;
	return (diffuseOutput + specularOutput);
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

float DirectionalLightShadowCalculation(int i, int splitIndex, DirectionalLight light, vec3 fragPos, vec3 normal)
{
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

	float blockerDistance = (avgDistance / blockers);
	float penumbraWidth = (projCoords.z - blockerDistance) / blockerDistance * lightSize;
	float texelSize = penumbraWidth * PCSSScaleFactor / DirectionalLights[i].lightFrustumWidth[splitIndex] * DirectionalLights[i].lightFrustumDistance[splitIndex] / 100.0;

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
		shadow += texture(pointShadowMap, vec4((fragToLight + gridSamplingDisk[j] * diskRadius), i)).r;
	}
	shadow /= float(samples);
	return shadow;
}
