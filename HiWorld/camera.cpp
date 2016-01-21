#include "camera.h"


camera::camera(vec3 p, vec3 f, vec3 u) {
	position = p;
	up = u;
	front = f;
}

void camera::tranclate(vec3 v) {
	position = position + v;
}

void camera::rotate(vec3 v, float angle) {
	
}

mat4 camera::m() {
	return lookAt(position, position + front, up);
}