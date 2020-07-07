layout (location = 0) out vec4 vFragColor;

in GS_OUT {
    vec2 TexCoords;
	flat int splitIndex;
} vs_in;

//uniform
uniform sampler2DArray textureMapArray;	//the input image to blur

//constant kernel values for Gaussian smoothing
const float kernel[] = float[11](
0.0093,	0.028002,	0.065984,	0.121703,	0.175713,	0.198596,	0.175713,	0.121703,	0.065984,	0.028002,	0.0093
);
void main()
{ 
	//get the inverse of texture size
	float delta = 1.0 / textureSize(textureMapArray, 0).x;
	vec4 color = vec4(0);
	int  index = 10;
	 
	//go through all neighbors and multiply the kernel value with the obtained 
	//colour from the input image
	for(int i = -5; i <= 5; i++) {
		vec4 sp = texture(textureMapArray, vec3(vs_in.TexCoords.x + i * delta, vs_in.TexCoords.y, vs_in.splitIndex));
		sp = kernel[i + 5] * sp;
		color += sp;
	}
	//return the filtered colour as fragment output
    vFragColor = color;
}