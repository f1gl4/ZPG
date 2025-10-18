#version 330

layout(location=0) in vec3 vp;

uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;

void main () {
	gl_Position = projection * view * modelMatrix * vec4(vp, 1.0);
}