layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 5) in vec2 aTexCoords;



out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

out DirectionalLightSpaces {
    float Distance;
    vec4 FragPosLightSpaces[DIRECTIONAL_LIGHTS_AMOUNT];
} dls_out;

uniform mat4 model;

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;

    gl_Position = CameraProjection * CameraView * vec4(vs_out.FragPos, 1.0);

    dls_out.Distance = distance(gl_Position.xyz, CameraPosition);

    if(dls_out.Distance < SplitDistance0){
        for(int i = 0; i < DirectionalLightCount; i++){
            dls_out.FragPosLightSpaces[i] = DirectionalLights[i].lightSpaceMatrix[0] * vec4(vs_out.FragPos, 1.0);
        }
    }else if(dls_out.Distance < SplitDistance1){
        for(int i = 0; i < DirectionalLightCount; i++){
            dls_out.FragPosLightSpaces[i] = DirectionalLights[i].lightSpaceMatrix[1] * vec4(vs_out.FragPos, 1.0);
        }
    }else if(dls_out.Distance < SplitDistance2){
        for(int i = 0; i < DirectionalLightCount; i++){
            dls_out.FragPosLightSpaces[i] = DirectionalLights[i].lightSpaceMatrix[2] * vec4(vs_out.FragPos, 1.0);
        }
    }else if(dls_out.Distance < SplitDistance3){
        for(int i = 0; i < DirectionalLightCount; i++){
            dls_out.FragPosLightSpaces[i] = DirectionalLights[i].lightSpaceMatrix[3] * vec4(vs_out.FragPos, 1.0);
        }
    }
}