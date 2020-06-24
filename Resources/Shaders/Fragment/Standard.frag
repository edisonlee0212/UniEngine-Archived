
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpaces0[DIRECTIONAL_LIGHTS_AMOUNT];
    //vec4 FragPosLightSpaces1[DIRECTIONAL_LIGHTS_AMOUNT];
    //vec4 FragPosLightSpaces2[DIRECTIONAL_LIGHTS_AMOUNT];
    //vec4 FragPosLightSpaces3[DIRECTIONAL_LIGHTS_AMOUNT];
} fs_in;

void main()
{    
    // properties
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(CameraPosition - fs_in.FragPos);

    vec3 color = texture(TEXTURE_DIFFUSE[0], fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.3 * color;

    vec3 result = CalculateLights(
        fs_in.FragPosLightSpaces0, 
        //fs_in.FragPosLightSpaces1,
        //fs_in.FragPosLightSpaces2,
        //fs_in.FragPosLightSpaces3,
        norm, viewDir, fs_in.FragPos);

    FragColor = vec4((ambient + result) * color, 1.0);
}
