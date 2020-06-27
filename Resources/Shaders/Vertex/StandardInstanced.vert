layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 5) in vec2 aTexCoords;
layout (location = 12) in mat4 aInstanceMatrix;


out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
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
    vs_out.Normal = mat3(transpose(inverse(matrix))) * aNormal;
    vs_out.TexCoords = aTexCoords;    

    gl_Position =  CameraProjection * CameraView * vec4(vs_out.FragPos, 1.0);

    dls_out.Distance = gl_Position.z;
}