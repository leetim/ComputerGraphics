#version 330 core

layout (location = 0) in vec3 position;
uniform mat4 view;
uniform mat4 frustum;

void main(){
	gl_Position = frustum * view * vec4(position, 1.0);
}