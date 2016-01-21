#pragma once
#include "Matrix.h"

class camera {
public:
	camera(vec3 position, vec3 front, vec3 up);
	void tranclate(vec3 v);
	void rotate(float pitch_angle, float yaw_angle);
	void zoom(float k);
	void scale(vec3 v, float k);
	void move(char dir);
	mat4 m();	
private:
	float cnear;
	float cfar;
	float cfovy;
	float speed;
	float pitch;
	float yaw;
	vec3 front;
	vec3 up;
	vec3 position;
};