#include "buffers.h"

Buffer::Buffer() {

}

Buffer::Buffer(GLenum m, float* a, int c, Vec4& col) {
	count = c;
	mode = m;
	color = col;
	glGenBuffers(1, &number);
	glBindBuffer(GL_ARRAY_BUFFER, number);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * c, a, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::draw(const GLuint& un_color, const GLuint& at_vertex) {
	float* cl = color.getArray();
	glUniform4fv(un_color, 1, color.getArray());
	glBindBuffer(GL_ARRAY_BUFFER, number);
	glVertexAttribPointer(at_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawArrays(mode, 0, count);
}