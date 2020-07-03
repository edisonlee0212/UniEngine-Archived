layout (location = 0) out vec4 vFragColor;

in GS_OUT {
    vec2 TexCoords;
	flat int splitIndex;
} vs_in;
//uniform
uniform sampler2DArray textureMapArray;	//the input image to blur

//constant kernel values for Gaussian smoothing
const float kernel[] = float[21](0.000272337,  0.00089296, 0.002583865, 0.00659813,  0.014869116,
								 0.029570767, 0.051898313, 0.080381679, 0.109868729, 0.132526984, 
								 0.14107424,  0.132526984, 0.109868729, 0.080381679, 0.051898313, 
								 0.029570767, 0.014869116, 0.00659813,  0.002583865, 0.00089296, 0.000272337);
uniform int lightIndex;
void main()
{ 
	//get the inverse of texture size
	float delta = 1.0 / textureSize(textureMapArray, 0).y;
	vec4 color = vec4(0);
	int  index = 20;
	 
	//go through all neighbors and multiply the kernel value with the obtained 
	//colour from the input image
	for(int i = -10; i <= 10; i++) {
		vec4 sp = texture(textureMapArray, vec3(vs_in.TexCoords.x, vs_in.TexCoords.y + i * delta, lightIndex * 4 + vs_in.splitIndex));
		sp = kernel[i + 10] * sp;
		color += sp;
	}
	//return the filtered colour as fragment output
    vFragColor = color;
}