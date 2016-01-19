#pragma once
#include <glew.h>
#include <freeglut.h>
#include "Matrix.h"

class Buffer {
public:
	Buffer();
	Buffer(GLenum mode, float* ar, int count, Vec4& color);
	void draw(const GLuint& un_color, const GLuint& at_vertex);
private:
	GLuint number;
	GLenum mode;
	int count;
	Vec4 color;
};