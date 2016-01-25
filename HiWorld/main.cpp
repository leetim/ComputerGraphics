#define FA_COUNT 6
#define WHEEL_DOWN 0x0003
#define WHEEL_UP 0x0004
#define MIN_FOVY 44.0f
#define MAX_FOVY 46.0f
#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Matrix.h"
#include "buffers.h"
#include "camera.h"
#include <windows.h>
#include <SOIL.h>

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
GLint u_frustum;
GLint u_view;
int width = 800;
int height = 800;
float fovy = 45.0f;
camera cam(vec3(0.0f, 1.0f, 0.0f), vec3(0.9f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

GLuint texture;

int OpenGLItit(int argc, char* argv[], char* caption){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
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

	mat4 m = glm::perspective(fovy, (float)width/height, 0.1f, 100000.0f);
	//mat4 m = glm::ortho(-width/20.0f, width/20.0f, height/20.0f, -height/20.0f, 0.1f, 10000.0f);

	glUseProgram(Program);
	glUniformMatrix4fv(u_frustum, 1, GL_FALSE, glm::value_ptr(m));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(cam.m()));
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

	float lines[100][3] = { { 24, 0.0f, -25 },{ -25, 0.0f, -25 } };
	for (int i = 2; i < 100; i++) {
		lines[i][0] = ((i % 2) == 0) ? 24 : -25;
		lines[i][1] = lines[i - 1][1];
		lines[i][2] = lines[i - 1][2] + ((i + 1) % 2);
	}

	float lines2[100][3] = { { -25, 0.0f, -25 },{ -25, 0.0f, 24 } };
	for (int i = 2; i < 100; i++) {
		lines2[i][0] = lines2[i - 1][0] + ((i + 1) % 2);
		lines2[i][1] = lines2[i - 1][1];
		lines2[i][2] = ((i % 2) == 0) ? 24 : -25;
	}

	float lines3[6][3] = {
		{-50, 0, 0},
		{50, 0, 0},
		{0, -50, 0},
		{0, 50, 0},
		{0, 0, -50},
		{0, 0, 50}
	};

	float square[4][3] = {
		-1000.0f, -100.0, -1000.0f,
		-1000.0f, -100.0, 1000.0f,
		1000.0f, -100.0, 1000.0f,
		1000.0f, -100.0, -1000.0f,
	};

	b[0] = Buffer(GL_TRIANGLES, triangle, 9, Vec4(0.0f, 0.5f, 0.5f, 1.0f));
	b[1] = Buffer(GL_TRIANGLES, triangle2, 9, Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	b[2] = Buffer(GL_LINES, (float*)lines, 300, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	b[3] = Buffer(GL_LINES, (float*)lines2, 300, Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	b[4] = Buffer(GL_LINES, (float*)lines3, 18, Vec4(1.0f, 0.0f, 1.0f, 1.0f));
	b[5] = Buffer(GL_QUADS, (float*)square, 12, Vec4(0.3f, 0.3f, 0.3f, 1.0f));
}

int lastx = -1;
int lasty = -1;
bool to_center_flag = false;

void to_center() {
	int Cx = width / 2;
	int Cy = height / 2;
	to_center_flag = true;
	lastx = Cx;
	lasty = Cy;
	glutWarpPointer(Cx, Cy);
}
/*
void make_texture() {
	int image_width;
	int image_height;
	glGenTextures(1, &texture);
	unsigned char* image = SOIL_load_image("textures\grass.jpg", &image_width, &image_height, 0, SOIL_LOAD_RGB);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D);
}
*/
void mouse_move(int x, int y) {
	if (to_center_flag && x == width / 2 && y == height / 2) {
		to_center_flag = false;
		return;
	}
	if (lastx == -1 && lasty == -1) {
		lastx = x;
		lasty = y;
	}
	int offset_x = x - lastx;
	int offset_y = lasty - y;
	cam.rotate(offset_y * 0.1, offset_x * 0.1);
	glutPostRedisplay();
	to_center();
}



void mouse_click(int button, int state, int x, int y) {
	switch (button){
	case WHEEL_UP:
		fovy += 0.1f;
		break;
	case WHEEL_DOWN:
		fovy -= 0.1f;
		break;
	}
	if (fovy < MIN_FOVY) {
		fovy = MIN_FOVY;
	}
	if (fovy > MAX_FOVY) {
		fovy = MAX_FOVY;
	}
	glutPostRedisplay();
	cout << button << " " << fovy << endl;
	ShowCursor(false);
}

void key_press_event(unsigned char key, GLint x, GLint y){
	cam.move((char)key);
	switch (key) {
	case 'q':
		cam.rotate(0, -1.0);
		break;
	case 'e':
		cam.rotate(0, 1.0);
		break;
	}
	glutPostRedisplay();
}

void reshape_event(int a_width, int a_height) {
	width = a_width;
	height = a_height;
	glViewport(0, 0, width, height);
	glutPostRedisplay();
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
	u_frustum = glGetUniformLocation(program, "frustum");
	u_view = glGetUniformLocation(program, "view");
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
	glutWarpPointer(width / 2, height / 2);
	
	glutPassiveMotionFunc(mouse_move);
	glutMouseFunc(mouse_click);
	glutReshapeFunc(reshape_event);
	glutDisplayFunc(display);
	glutKeyboardFunc(key_press_event);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
  glutMainLoop();

	//FreeAll();
  return 0;
}