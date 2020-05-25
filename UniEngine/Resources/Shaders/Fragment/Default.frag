out vec4 FragColor;

in vec2 TexCoords;

void main()
{    
    FragColor = texture(TEXTURE_DIFFUSE[0], TexCoords);
}