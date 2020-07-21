layout (location = 0) out vec4 vFragColor;

in GS_OUT {
    vec2 TexCoords;
	flat int splitIndex;
} vs_in;

//uniform
uniform sampler2DArray textureMapArray;	//the input image to blur

//constant kernel values for Gaussian smoothing
const float kernel11[] = float[11](
0.000003,	0.000229,	0.005977,	0.060598,	0.24173,	0.382925,	0.24173,	0.060598,	0.005977,	0.000229,	0.000003
);

const float kernel7[] = float[7](
0.00598,	0.060626,	0.241843,	0.383103,	0.241843,	0.060626,	0.00598
);

const float kernel5[] = float[5](
0.06136,	0.24477,	0.38774,	0.24477,	0.06136
);
const float kernel3[] = float[3](
0.27901,	0.44198,	0.27901
);

void main()
{ 
	//get the inverse of texture size
	float delta = 1.0 / textureSize(textureMapArray, 0).x;
	vec2 color = vec2(0);	 
	//go through all neighbors and multiply the kernel value with the obtained 
	//colour from the input image
	for(int i = -1; i <= 1; i++) {
		color += texture(textureMapArray, vec3(vs_in.TexCoords.x + i * delta, vs_in.TexCoords.y, vs_in.splitIndex)).rg * kernel3[i + 1];
	}
	//return the filtered colour as fragment output
	vFragColor = vec4(color, 0, 1);
}