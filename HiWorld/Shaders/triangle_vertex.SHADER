#version 330 core

in vec3 position;
uniform mat4 m;

void main(){
	vec4 v = m * vec4(position, 1.0);
	v.x /= v.w;
	v.y /= v.w;
	v.z /= v.w;
	v.w = 1.0;
	gl_Position = v; // ec4(position, 1.0); // v;
}