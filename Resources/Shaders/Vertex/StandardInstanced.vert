layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 4) in vec2 aTexCoords;
layout (location = 12) in mat4 aInstanceMatrix;


out VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	mat3 TBN;
	vec2 TexCoords;
} vs_out;

out DirectionalLightSpaces {
	float Distance;
} dls_out;


uniform mat4 model;

void main()
{
	mat4 matrix = model * aInstanceMatrix;
	vs_out.FragPos = vec3(matrix * vec4(aPos, 1.0));
	vs_out.Normal = normalize(transpose(inverse(mat3(matrix))) * aNormal);
	vec3 T = normalize(vec3(matrix * vec4(aTangent,   0.0)));
	vec3 N = normalize(vec3(matrix * vec4(aNormal,    0.0)));
	// re-orthogonalize T with respect to N
	T = normalize(T - dot(T, N) * N);
	// then retrieve perpendicular vector B with the cross product of T and N
	vec3 B = cross(N, T);
	vs_out.TBN = mat3(T, B, N);
	vs_out.TexCoords = aTexCoords;    

	gl_Position =  CameraProjection * CameraView * vec4(vs_out.FragPos, 1.0);

	dls_out.Distance = gl_Position.z;
}