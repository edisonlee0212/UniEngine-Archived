out vec4 FragColor;
void main()
{
    FragColor = vec4(gl_FragCoord.z, gl_FragCoord.z * gl_FragCoord.z, 0, 1);
}