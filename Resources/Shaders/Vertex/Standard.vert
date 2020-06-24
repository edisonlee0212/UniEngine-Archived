layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 5) in vec2 aTexCoords;



out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpaces0[DIRECTIONAL_LIGHTS_AMOUNT];
    //vec4 FragPosLightSpaces1[DIRECTIONAL_LIGHTS_AMOUNT];
    //vec4 FragPosLightSpaces2[DIRECTIONAL_LIGHTS_AMOUNT];
    //vec4 FragPosLightSpaces3[DIRECTIONAL_LIGHTS_AMOUNT];
} vs_out;

uniform mat4 model;

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    for(int i = 0; i < DirectionalLightCount; i++){
        vs_out.FragPosLightSpaces0[i] = DirectionalLights[i].lightSpaceMatrix0 * vec4(vs_out.FragPos, 1.0);
        //vs_out.FragPosLightSpaces1[i] = DirectionalLights[i].lightSpaceMatrix1 * vec4(vs_out.FragPos, 1.0);
        //vs_out.FragPosLightSpaces2[i] = DirectionalLights[i].lightSpaceMatrix2 * vec4(vs_out.FragPos, 1.0);
        //vs_out.FragPosLightSpaces3[i] = DirectionalLights[i].lightSpaceMatrix3 * vec4(vs_out.FragPos, 1.0);
    }

    gl_Position = CameraProjection * CameraView * vec4(vs_out.FragPos, 1.0);
}