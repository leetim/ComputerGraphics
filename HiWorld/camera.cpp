#include "camera.h"
#include <iostream>

using namespace std;

camera::camera(vec3 p, vec3 f, vec3 u) {
	position = p;
	up = normalize(u);
	front = normalize(f);
	speed = 0.2f;
	rotate(0.0f, 0.0f);
}

void camera::move(char dir) {
	if (dir == 'W') {
		position += speed * front * 100.0f;
	}
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

void camera::rotate(float a_pitch, float a_yaw) {
	pitch += radians(a_pitch);
	yaw += radians(a_yaw);
	cout << pitch << " " << yaw << endl;
	if (pitch > 3.1 / 2) {
		pitch = 3.0 / 2;
	}
	if (pitch < -3.1 / 2) {
		pitch = -3.0 / 2;
	}
	front.x = cos(pitch) * cos(yaw);
	front.y = sin(pitch);
	front.z = cos(pitch) * sin(yaw);
	front = normalize(front);
}

mat4 camera::m() {
	return lookAt(position, position + front, up);
}