layout (location = 0) out vec4 vFragColor;


uniform int index;

void main()
{
	float depth = gl_FragCoord.z;
	switch(SoftShadowMode){
		case 1:
			vFragColor = vec4(depth, depth * depth, 0, 1);
			break;
		case 2:
			vFragColor = vec4(exp(depth * EVSMExponent), 0, 0, 1);
			break;
		default:
			vFragColor = vec4(depth, 0, 0, 1);
			break;
	}
}