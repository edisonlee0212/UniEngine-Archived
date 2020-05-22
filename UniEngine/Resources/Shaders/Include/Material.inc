struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    sampler2D height;
    float shininess;
};

uniform Material materials[MAX_MATERIALS_AMOUNT];