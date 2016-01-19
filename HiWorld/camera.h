#pragma once
#include "Matrix.h"

class camera {
public:
	void tranclate(Vec4 v);
	void rotate(Vec4 v, float angle);
	void zoom(float k);
	void scale(Vec4 v, float k);
	Mat4 m();
private:
	float near;
	float far;
	float fovy;
	Vec4 target;
	Vec4 side;
	Vec4 position;
};