layout (location = 0) out vec4 vFragColor;
uniform bool enableVSM;
void main()
{
    float depth = gl_FragCoord.z;
    if(enableVSM){
        vFragColor = vec4(depth, depth * depth, 0, 1);
    }else{
        vFragColor = vec4(depth, 0, 0, 1);
    }
}