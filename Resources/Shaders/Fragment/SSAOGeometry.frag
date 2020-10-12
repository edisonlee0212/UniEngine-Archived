out float FragColor;

in VS_OUT {
	vec2 TexCoords;
} fs_in;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D texNoise;

uniform vec3 samples[64];

// parameters (you'd probably want to use them as uniforms to more easily tweak the effect)
uniform int kernelSize;
uniform float radius;
uniform float bias;
uniform float factor;
// tile noise texture over screen based on screen dimensions divided by noise size
uniform vec2 noiseScale; 

void main()
{
    // get input for SSAO algorithm
    vec3 fragPos = vec3(CameraView * vec4(texture(gPosition, fs_in.TexCoords).xyz, 1.0));
    vec3 normal = normalize(texture(gNormal, fs_in.TexCoords).rgb);
    if(normal == vec3(0.0)) discard;
    normal = normalize(mat3(CameraView) * normal);
    vec3 randomVec = normalize(texture(texNoise, fs_in.TexCoords * noiseScale).xyz);
    // create TBN change-of-basis matrix: from tangent-space to view-space
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);
    // iterate over the sample kernel and calculate occlusion factor
    float occlusion = 0.0;
    int validAmount = 0;
    for(int i = 0; i < kernelSize; ++i)
    {
        // get sample position
        vec3 samplePos = TBN * samples[i]; // from tangent to view-space
        samplePos = fragPos + samplePos * radius; 
        
        // project sample position (to sample texture) (to get position on screen/texture)
        vec4 offset = vec4(samplePos, 1.0);
        offset = CameraProjection * offset; // from view to clip-space
        offset.xyz /= offset.w; // perspective divide
        offset.xyz = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0
        if(texture(gNormal, offset.xy).xyz == vec3(0.0)) continue;
        validAmount = validAmount + 1;
        // get sample depth
        float sampleDepth = vec3(CameraView * texture(gPosition, offset.xy)).z; // get depth value of kernel sample
        
        // range check & accumulate
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;           
    }
    if(validAmount == 0){
        FragColor = 1.0;
    }else{
        FragColor = pow(1.0 - (occlusion / validAmount), factor);
    }
}