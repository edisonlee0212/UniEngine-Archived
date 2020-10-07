in vec4 FragPos;


uniform int index;

void main()
{
    float lightDistance = length(FragPos.xyz - PointLights[index].position);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / PointLights[index].constantLinearQuadFarPlane.w;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}