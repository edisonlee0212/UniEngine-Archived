layout (location = 0) out float vFragColor;


uniform int index;

void main()
{
	vFragColor = gl_FragCoord.z;
}