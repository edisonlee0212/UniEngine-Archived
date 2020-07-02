layout (location = 0) out vec4 vFragColor;

smooth in vec2 TexCoords;

//uniform
uniform sampler2D textureMap;	//the input image to blur

//constant kernel values for Gaussian smoothing
const float kernel[] = float[21](0.000272337,  0.00089296, 0.002583865, 0.00659813,  0.014869116,
								 0.029570767, 0.051898313, 0.080381679, 0.109868729, 0.132526984, 
								 0.14107424,  0.132526984, 0.109868729, 0.080381679, 0.051898313, 
								 0.029570767, 0.014869116, 0.00659813,  0.002583865, 0.00089296, 0.000272337);
 
void main()
{ 
	//get the inverse of texture size
	vec2 delta = 1.0 / textureSize(textureMap, 0);
	vec4 color = vec4(0);
	int  index = 20;
	 
	//go through all neighbors and multiply the kernel value with the obtained 
	//colour from the input image
	for(int i = -10; i <= 10; i++) {				
		color += kernel[index--] * texture(textureMap, TexCoords + (vec2(i * delta.x, 0)));
	}
	  
	//return the filtered colour as fragment output
    vFragColor = vec4(color.xy, 0, 0);	
}