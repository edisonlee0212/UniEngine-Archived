out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform vec3 lightDir;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
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
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
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



void main()
{    
    // properties
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(CameraPosition - fs_in.FragPos);

    vec3 color = texture(TEXTURE_DIFFUSE[0], fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.3 * color;

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, norm, lightDir);

    vec3 result = CalculateLights(norm, viewDir, fs_in.FragPos);

    FragColor = vec4((ambient + (1.0 - shadow) * result) * color, 1.0);
}
