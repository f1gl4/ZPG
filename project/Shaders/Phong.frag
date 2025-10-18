#version 330 core

#define MAX_LIGHTS 8

struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
    float cutoff;
    float outerCutoff;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 cameraPosition;

uniform sampler2D textureUnitID;
uniform int useTexture;

in vec4 worldPosition;
in vec3 worldNormal;
in vec3 viewDir;
in vec2 uv;

out vec4 fragColor;

void main() {
    vec3 ambient = vec3(0.05);
    vec3 result = ambient;

    vec3 normal = normalize(worldNormal);
    vec3 textureColor = vec3(1.0);

    if (useTexture == 1) {
        textureColor = texture(textureUnitID, uv).rgb;
    }

    for (int i = 0; i < numberOfLights; i++) {
        vec3 lightDir = normalize(lights[i].position - worldPosition.xyz);
        float attenuation = 1.0;
        float intensity = 1.0;

        float distance = length(lights[i].position - worldPosition.xyz);
        attenuation = 1.0 / (lights[i].constant +
                             lights[i].linear * distance +
                             lights[i].quadratic * distance * distance);

        if (lights[i].cutoff > 0.0) {
            float theta = dot(lightDir, normalize(-lights[i].direction));
            if (theta > lights[i].outerCutoff) {
                float epsilon = lights[i].cutoff - lights[i].outerCutoff;
                intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
            } else {
                intensity = 0.0;
            }
        }

        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color;

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = spec * lights[i].color;

        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;

        result += diffuse + specular;
    }

    fragColor = vec4(result * textureColor, 1.0);
}
