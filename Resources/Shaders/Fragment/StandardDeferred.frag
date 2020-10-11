layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	mat3 TBN;
	vec2 TexCoords;
} fs_in;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    gPosition.rgb = fs_in.FragPos;
	gPosition.a = 1.0;

	vec3 albedo = texture(TEXTURE_DIFFUSE0, fs_in.TexCoords).rgb;
    vec3 normal;
	if(enableNormalMapping){
		normal = texture(TEXTURE_NORMAL0, fs_in.TexCoords).rgb;
		normal = normal * 2.0 - 1.0;   
		normal = normalize(fs_in.TBN * normal); 
	}else{
		normal = fs_in.Normal;
	}
    // also store the per-fragment normals into the gbuffer
    gNormal.rgb = normalize(normal);
	gNormal.a = material.shininess;
    // store specular intensity in gAlbedoSpec's alpha component
    float specular = 1.0;
	if(enableSpecularMapping){
		specular = texture(TEXTURE_SPECULAR0, fs_in.TexCoords).r;
	}

	gAlbedoSpec.rgb = albedo;
	gAlbedoSpec.a = specular;
}