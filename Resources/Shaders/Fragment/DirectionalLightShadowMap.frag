layout (location = 0) out vec4 vFragColor;

layout (std140, binding = 4) uniform ShadowSettings
{
    float SplitDistance0;
    float SplitDistance1;
    float SplitDistance2;
    float SplitDistance3;
    float EnableVSM;
	float EnableEVSM;
	float DisplaySplit;
	float SeamFixRatio;
};

void main()
{
    float depth = gl_FragCoord.z;
    if(EnableVSM != 0){
        if(EnableEVSM != 0){
            depth = depth * 2.0 - 1.0;
            float pos = exp(40.0 * depth);
            float neg = exp(-40.0 * depth);
            vFragColor = vec4(pos, pos * pos, neg, neg * neg);
        }else{
            vFragColor = vec4(depth, depth * depth, 0, 1);
        }
    }else{
        vFragColor = vec4(depth, 0, 0, 1);
    }
}