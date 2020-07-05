out vec4 FragColor;
void main()
{
    float depth = gl_FragCoord.z;
    FragColor = vec4(depth, depth * depth, 0, 1);
}