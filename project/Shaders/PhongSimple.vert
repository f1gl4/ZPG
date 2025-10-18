#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 norm;
uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;

out vec4 worldPosition;
out vec3 worldNormal;
out vec3 viewDir;

void main(void) {
    // vertex pos in world
    worldPosition = modelMatrix * vec4(vp, 1.0f);
    
    // normal in world
    worldNormal = normalize(mat3(transpose(inverse(modelMatrix))) * norm);

    // camera pos in world
    viewDir = normalize(cameraPosition - worldPosition.xyz);

    // final pos vertex in clip space
    gl_Position = projection * view * worldPosition;
}
