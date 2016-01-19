#define FA_COUNT 4
#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Matrix.h"
#include "buffers.h"

using namespace std;

struct NewString {
	char* s;
	int l;
} ;

static vector <GLuint> Shaders;
Buffer b[FA_COUNT];
GLuint Program;
GLuint buf[FA_COUNT];
Vec4 colors[FA_COUNT] = {
	Vec4(0.0f, 0.0f, 0.0f, 1.0f),
	Vec4(1.0f, 0.0f, 0.0f, 1.0f),
	Vec4(0.0f, 1.0f, 0.0f, 1.0f),
	Vec4(0.0f, 0.0f, 1.0f, 1.0f)
};
GLint u_color;
GLint a_vertex;
GLint u_mat;

int OpenGLItit(int argc, char* argv[], char* caption){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(caption);
	glewExperimental = GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		return 1;
	}
	return 0;
}

NewString ReadFile(char* fileName) {
	ifstream input(fileName, ios::in);
	NewString res;
	if (!input.is_open()) {
		res.s = NULL;
		res.l = -1;
		return res;
	}
	input.seekg(0, ios::end);
	res.l = input.tellg();
	input.seekg(0, ios::beg);
	res.s = new char[1 + res.l];
	input.read(res.s, res.l);
	input.close();
	res.s[res.l] = 0;
	return res;
}

GLuint LoadShader(char* fileName, GLenum shaderType) {
	GLuint p = glCreateShader(shaderType);
	GLint status = GL_FALSE;
	NewString shSource = ReadFile(fileName);
	if (shSource.s == NULL) {
		cout << fileName << " not found" << endl;
		return GL_UNSIGNED_INT;
	}
	glShaderSource(p, sizeof(char), &shSource.s, &shSource.l);
	glCompileShader(p);
	glGetShaderiv(p, GL_COMPILE_STATUS, &status);
	if (!status) {
		NewString log;
		log.s = new char[status];
		glGetShaderiv(p, GL_INFO_LOG_LENGTH, &status);
		glGetShaderInfoLog(p, status + 1, &log.l, log.s);
		cout << "Shader compilation Error" << endl;
		cout << log.s << endl;
		delete log.s;
		return GL_UNSIGNED_INT;
	}
	delete shSource.s;
	return p;
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 m = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);
	float z[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, -2,
		0, 0, -1, 0
	};

	glUseProgram(Program);
	glUniformMatrix4fv(u_mat, 1, GL_FALSE, glm::value_ptr(m));
	glEnableVertexAttribArray(a_vertex);
	for (int i = 0; i < FA_COUNT; i++) {
		b[i].draw(u_color, a_vertex);
	}

	glDisableVertexAttribArray(a_vertex);
	glUseProgram(0);

	glutSwapBuffers();
}

void GetBuffer(){

	float triangle[] = {
		-1.0f, -1.0f,  10.0f,
		0.0f,  1.0f,  10.0f,
		1.0f, -1.0f,  10.0f
	};

	float triangle2[] = {
		-1.0f,  1.0f,  15.0f,
		0.0f, -1.0f,  5.0f,
		1.0f,  1.0f,  15.0f
	};

	float lines[100][3] = { { 25, -4.5, -50 },{ -25, -4.5, -50 } };
	for (int i = 2; i < 100; i++) {
		lines[i][0] = ((i % 2) == 0) ? 25 : -25;
		lines[i][1] = lines[i - 1][1];
		lines[i][2] = lines[i - 1][2] + ((i + 1) % 2);
	}

	float lines2[100][3] = { { -25, -4.5, -50 },{ -25, -4.5, -5 } };
	for (int i = 2; i < 100; i++) {
		lines2[i][0] = lines2[i - 1][0] + ((i + 1) % 2);
		lines2[i][1] = lines2[i - 1][1];
		lines2[i][2] = ((i % 2) == 0) ? -25 : 25;
	}

	b[0] = Buffer(GL_TRIANGLES, triangle, 9, Vec4(0.0f, 0.0f, 0.0f, 1.0f));
	b[1] = Buffer(GL_TRIANGLES, triangle2, 9, Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	b[2] = Buffer(GL_LINES, (float*)lines, 300, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	b[3] = Buffer(GL_LINES, (float*)lines2, 300, Vec4(0.0f, 0.0f, 1.0f, 1.0f));

}



GLuint LoadShaderProgram(){
	GLuint program = glCreateProgram(),
		vShader = LoadShader("Shaders/triangle_vertex.SHADER", GL_VERTEX_SHADER),
		fShader = LoadShader("Shaders/triangle_geometry.SHADER", GL_FRAGMENT_SHADER);
	GLint status = GL_UNSIGNED_INT;
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		return GL_UNSIGNED_INT;
	}
	u_color = glGetUniformLocation(program, "color");
	u_mat = glGetUniformLocation(program, "m");
	a_vertex = glGetAttribLocation(program, "position");
	return program;
}

void FreeAll() {

	glUseProgram(0);
	glDeleteProgram(Program);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, buf);
}

int main(int argc, char* argv[]){
	if (OpenGLItit(argc, argv, "Triangle")) {
		cout << "Can't include OpenGL modules" << endl;
		return 1;
	}
	Program = LoadShaderProgram();
	GetBuffer();

	glutDisplayFunc(display);
	glClearColor(256, 256, 256, 256);
	glEnable(GL_DEPTH_TEST);
  glutMainLoop();

	//FreeAll();
  return 0;
}