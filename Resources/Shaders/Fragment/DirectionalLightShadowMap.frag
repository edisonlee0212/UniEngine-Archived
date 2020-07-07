out vec4 FragColor;
uniform bool enableVSM;
void main()
{
    float depth = gl_FragCoord.z;
    if(enableVSM){
        FragColor = vec4(depth, depth * depth, 0, 1);
    }else{
        FragColor = vec4(depth, 0, 0, 1);
    }
}