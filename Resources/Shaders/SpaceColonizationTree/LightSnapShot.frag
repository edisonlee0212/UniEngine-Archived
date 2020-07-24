layout (location = 0) out vec4 vFragColor;

void main()
{
	float depth = gl_FragCoord.z;
	vFragColor = vec4(depth, 0, 0, 1);
}