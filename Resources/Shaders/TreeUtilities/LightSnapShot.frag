layout (location = 0) out vec4 vFragColor;

in VS_OUT {
	flat uint LeafIndex;
	float distance;
} fs_in;

void main()
{
	//gl_FragCoord.z
	uint index = fs_in.LeafIndex;
	uint r = index % 256;
	index = (index - r) / 256;
	uint g = index % 256;
	index = (index - g) / 256;

	vec3 color = vec3(r, g, index);
	vFragColor = vec4(fs_in.LeafIndex, 1.0 - gl_FragCoord.z, 0, 1);
}