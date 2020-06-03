out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D directionalShadowMap;
uniform vec3 directionalLightPos;
uniform vec3 directionalLightDir;

uniform samplerCube pointShadowMap;
uniform vec3 pointLightPos;
uniform float farPlane;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float DirectionalLightShadowCalculation(sampler2D shadowMap, vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{

    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    if(projCoords.z > 1.0)
        return 0.0;

    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // calculate bias
    float bias = max(0.01 * (1.0 - dot(normal, lightDir)), 0.005);
    //float bias = 0.005;
    
    // check whether current frag pos is in shadow
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    return shadow;
}

float PointLightShadowCalculation(samplerCube depthMap, vec3 fragPos, vec3 viewPos, vec3 lightPos, float far_plane)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    
    float currentDepth = length(fragToLight);
    
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
    return shadow;
}

void main()
{    
    // properties
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(CameraPosition - fs_in.FragPos);

    vec3 color = texture(TEXTURE_DIFFUSE[0], fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.3 * color;

    float directionalLightshadow = DirectionalLightShadowCalculation(directionalShadowMap, fs_in.FragPosLightSpace, norm, directionalLightDir);
    float pointLightShadow = PointLightShadowCalculation(pointShadowMap, fs_in.FragPos, CameraPosition, pointLightPos, farPlane);

    vec3 result = CalculateLights(norm, viewDir, fs_in.FragPos);

    FragColor = vec4((ambient + (1.0 - directionalLightshadow - pointLightShadow) * result) * color, 1.0);
}
