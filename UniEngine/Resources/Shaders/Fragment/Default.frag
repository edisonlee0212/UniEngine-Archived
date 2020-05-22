out vec4 FragColor;

in vec2 TexCoords;

void main()
{    
    FragColor = texture(materials[0].diffuse, TexCoords);
}