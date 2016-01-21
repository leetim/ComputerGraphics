#include "camera.h"


camera::camera(vec3 p, vec3 f, vec3 u) {
	position = p;
	up = normalize(u);
	front = normalize(f);
	speed = 0.2f;
}

void camera::move(char dir) {
	if (dir == 'w') {
		position += speed * front;
	}
	if (dir == 's') {
		position -= speed * front;
	}
	if (dir == 'a') {
		position -= speed * cross(front, up);
	}
	if (dir == 'd') {
		position += speed * cross(front, up);
	}
	if (dir == 'r') {
		position += speed * up;
	}
	if (dir == 'f') {
		position -= speed * up;
	}
}

void camera::rotate(float pitch_angle, float yaw_angle) {
	//pitch += radians(pitch);
	yaw += radians(yaw);
	if (pitch > 3.1 / 2) {
		pitch = 3.1 / 2;
	}
	if (pitch < -3.1 / 2) {
		pitch = -3.1 / 2;
	}
	front.x = cos(pitch) * cos(yaw);
	front.y = sin(pitch);
	front.z = cos(pitch) * sin(yaw);
	front = normalize(front);
}

mat4 camera::m() {
	return lookAt(position, position + front, up);
}