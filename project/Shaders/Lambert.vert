#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 norm;
uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;

out vec4 worldPosition;
out vec3 worldNormal;
//uniform mat3 normalMatrix; //(M-1)T

void main(void){
    gl_Position = (projection * view * modelMatrix) * vec4(vp, 1.0f);
    worldPosition = modelMatrix * vec4(vp, 1.0f);
    worldNormal = normalize(mat3(transpose(inverse(modelMatrix))) * norm);
}