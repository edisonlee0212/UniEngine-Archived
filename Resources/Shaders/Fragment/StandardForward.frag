out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec3 Tangent;
	vec2 TexCoords;
} fs_in;


void main()
{	
	vec4 textureColor = texture(UE_DIFFUSE_MAP, fs_in.TexCoords).rgba;
	if(UE_APLHA_DISCARD_ENABLED && textureColor.a < UE_APLHA_DISCARD_OFFSET)
        discard;
	float specular = 1.0;
	if(UE_SPECULAR_MAP_ENABLED){
		specular = texture(UE_SPECULAR_MAP, fs_in.TexCoords).r;
	}
	// properties
	vec3 normal = fs_in.Normal;
	if(UE_NORMAL_MAP_ENABLED){
		vec3 B = cross(fs_in.Normal, fs_in.Tangent);
		mat3 TBN = mat3(fs_in.Tangent, B, fs_in.Normal);
		normal = texture(UE_NORMAL_MAP, fs_in.TexCoords).rgb;
		normal = normal * 2.0 - 1.0;   
		normal = normalize(TBN * normal); 
	}
	
	vec3 viewDir = normalize(UE_CAMERA_POSITION - fs_in.FragPos);
	float dist = distance(fs_in.FragPos, UE_CAMERA_POSITION);
	
	vec3 F0 = vec3(0.04); 
	F0 = mix(F0, textureColor.rgb, UE_PBR_METALLIC);


	vec3 result = UE_FUNC_CALCULATE_LIGHTS(UE_ENABLE_SHADOW && UE_RECEIVE_SHADOW, UE_PBR_SHININESS, textureColor.rgb, specular, dist, normal, viewDir, fs_in.FragPos, UE_PBR_METALLIC, UE_PBR_ROUGHNESS, F0);
	FragColor = vec4(result + UE_AMBIENT_LIGHT * textureColor.rgb, textureColor.a);
}