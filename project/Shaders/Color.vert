#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;

out vec3 color;
void main () {
    gl_Position =  projection * view * modelMatrix * vec4 (vp, 1.0);
	color = normal;
}