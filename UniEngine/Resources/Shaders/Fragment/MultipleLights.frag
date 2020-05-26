out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(CameraPosition - FragPos);
    
    vec3 result = CalculateLights(norm, viewDir, FragPos);
    
    FragColor = vec4(result, 1.0) * texture(materials[0].diffuse, TexCoords);
}
