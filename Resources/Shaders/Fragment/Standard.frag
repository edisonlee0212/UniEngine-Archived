
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

in DirectionalLightSpaces {
    float Distance;
    vec4 FragPosLightSpaces[DIRECTIONAL_LIGHTS_AMOUNT];
} dls_in;



vec3 CalculateLights(vec3 normal, vec3 viewDir, vec3 fragPos);


vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);




float DirectionalLightShadowCalculation(int i, int splitIndex, DirectionalLight light, vec4 fragPosLightSpace, vec3 normal);
float PointLightShadowCalculation(int i, PointLight light, vec3 fragPos, vec3 normal);



void main()
{    
    // properties
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(CameraPosition - fs_in.FragPos);

    vec3 color = texture(TEXTURE_DIFFUSE[0], fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.3 * color;

    vec3 result = CalculateLights(norm, viewDir, fs_in.FragPos);

    if(dls_in.Distance < SplitDistance0){
        
    }else if(dls_in.Distance < SplitDistance1){
        ambient += vec3(0.2, 0.0, 0.0);
    }else if(dls_in.Distance < SplitDistance2){
        ambient += vec3(0.0, 0.2, 0.0);
    }else if(dls_in.Distance < SplitDistance3){
        ambient += vec3(0.0, 0.0, 0.2);
    }

    FragColor = vec4((ambient + result) * color, 1.0);
}



vec3 CalculateLights(vec3 normal, vec3 viewDir, vec3 fragPos){
    vec3 norm = normalize(normal);
    vec3 result = vec3(0.0, 0.0, 0.0);
    // phase 1: directional lighting
    for(int i = 0; i < DirectionalLightCount; i++){
        float shadow = 0.0;

        if(dls_in.Distance < SplitDistance0){
            shadow += DirectionalLightShadowCalculation(i, 0, DirectionalLights[i], dls_in.FragPosLightSpaces[i], norm);
        }else if(dls_in.Distance < SplitDistance1){
            shadow += DirectionalLightShadowCalculation(i, 1, DirectionalLights[i], dls_in.FragPosLightSpaces[i], norm);
        }else if(dls_in.Distance < SplitDistance2){
            shadow += DirectionalLightShadowCalculation(i, 2, DirectionalLights[i], dls_in.FragPosLightSpaces[i], norm);
        }else if(dls_in.Distance < SplitDistance3){
            shadow += DirectionalLightShadowCalculation(i, 3, DirectionalLights[i], dls_in.FragPosLightSpaces[i], norm);
        }

        result += CalcDirectionalLight(DirectionalLights[i], norm, viewDir) * (1.0 - shadow);
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
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
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
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
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
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
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

float DirectionalLightShadowCalculation(int i, int splitIndex, DirectionalLight light, vec4 fragPosLightSpace, vec3 normal)
{
    vec3 lightDir = light.direction;

    float bias = light.ReservedParameters.z;
    float normalOffset = light.ReservedParameters.w;

    // perform perspective divide
    vec3 projCoords = (fragPosLightSpace.xyz + normal * normalOffset) / fragPosLightSpace.w;

    if(projCoords.z > 1.0){
        return 0.0;
    }
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;


    // check whether current frag pos is in shadow
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0).xy;
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            shadow += texture(directionalShadowMap, vec4(projCoords.xy + vec2(x, y) * texelSize, i * 4 + splitIndex, currentDepth - bias)); 
        }    
    }
    shadow /= 9.0;
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
