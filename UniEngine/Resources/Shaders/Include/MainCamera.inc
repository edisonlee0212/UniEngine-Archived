layout (std140, binding = 0) uniform MainCameraBlock
{
    mat4 CameraProjection;
    mat4 CameraView;
    vec3 CameraPosition;
};