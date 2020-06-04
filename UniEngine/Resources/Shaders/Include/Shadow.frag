float DirectionalLightShadowCalculation(vec4[DIRECTIONAL_LIGHTS_AMOUNT] fragPosLightSpaces, vec3 normal);
float PointLightShadowCalculation(vec3 fragPos);


// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float DirectionalLightShadowCalculation(vec4[DIRECTIONAL_LIGHTS_AMOUNT] fragPosLightSpaces, vec3 normal)
{
    float sum = 0.0;
    for(int i = 0; i < DirectionalLightCount; i++){
        vec3 lightDir = DirectionalLights[i].direction;
        // perform perspective divide
        vec3 projCoords = fragPosLightSpaces[i].xyz / fragPosLightSpaces[i].w;

        if(projCoords.z > 1.0){
            continue;
        }
        // transform to [0,1] range
        projCoords = projCoords * 0.5 + 0.5;
        // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
        float closestDepth = texture(directionalShadowMap, vec3(projCoords.xy, i)).r; 
        // get depth of current fragment from light's perspective
        float currentDepth = projCoords.z;

        // calculate bias
        float bias = max(0.01 * (1.0 - dot(normal, lightDir)), 0.005);
        //float bias = 0.005;
    
        // check whether current frag pos is in shadow
        // PCF
        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0).xy;
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(directionalShadowMap, vec3(projCoords.xy + vec2(x, y) * texelSize, i)).r; 
                shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
            }    
        }
        shadow /= 9.0;
        sum = sum + shadow;
    }
    return sum;
}

float PointLightShadowCalculation(vec3 fragPos)
{
    vec3 viewPos = CameraPosition;
    float sum = 0.0;
    for(int i = 0; i < PointLightCount; i++){
        vec3 lightPos = PointLights[i].position;
        float far_plane = PointLights[i].constantLinearQuadFarPlane.w;
        // get vector between fragment position and light position
        vec3 fragToLight = fragPos - lightPos;
        float currentDepth = length(fragToLight);
        if(currentDepth > far_plane) continue;
        float shadow = 0.0;
        float bias = 0.2;
        int samples = 20;
        float viewDistance = length(viewPos - fragPos);
        float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
        for(int j = 0; j < samples; ++j)
        {
            float closestDepth = texture(pointShadowMap, fragToLight + gridSamplingDisk[j] * diskRadius).r;
            closestDepth *= far_plane;   // undo mapping [0;1]
            if(currentDepth - bias > closestDepth)
                shadow += 1.0;
        }
        shadow /= float(samples);
        sum = sum + shadow;
    }
    return sum;
}
