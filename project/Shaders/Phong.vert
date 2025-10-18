#version 330 core

layout(location=0) in vec3 vp;
layout(location=1) in vec3 norm;
layout(location=2) in vec2 vt;

uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;

out vec4 worldPosition;
out vec3 worldNormal;
out vec3 viewDir;
out vec2 uv;

void main() {
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNormal = normalize(normalMatrix * norm);
    worldPosition = modelMatrix * vec4(vp, 1.0);
    viewDir = normalize(cameraPosition - worldPosition.xyz);
    uv = vt;
    gl_Position = projection * view * worldPosition;
}
