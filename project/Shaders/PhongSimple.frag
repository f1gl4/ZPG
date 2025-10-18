#version 330

in vec4 worldPosition;
in vec3 worldNormal;
in vec3 viewDir;
uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec4 fragColor;

void main() {

    vec3 lightDir = normalize(lightPosition - worldPosition.xyz);

    // Ambient lighting
    vec4 ambient = 0.1 * vec4(lightColor, 1.0); 

    // Diffuse lighting
    float diff = max(dot(worldNormal, lightDir), 0.0);
    vec4 diffuse = diff * vec4(lightColor, 1.0);

    // Specular lighting
    vec3 reflectDir = reflect(-lightDir, worldNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec4 specular = spec * vec4(lightColor, 1.0);

    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

    fragColor = ambient + (diffuse * objectColor) + specular;
}
