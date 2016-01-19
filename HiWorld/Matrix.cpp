#define _USE_MATH_DEFINES
#include "Matrix.h"
#include <math.h>
#include <climits>

template <typename T> static void swap(T &a, T &b){
	T t;
	t = a;
	a = b;
	b = t;
}

class Permut {
	public:
		Permut(const int &k) {
			n = k;
			last = false;
			p.resize(k);
			for (int i = 0; i < n; i++) {
				p[i] = i;
			}
		}

		std::vector <int>& get(){
			return p;
		}

		int pairityCof() {
			int r = 0;
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (p[i] > p[j]) {
						r++;
					}
				}
			}
			return (r % 2 == 1) ? -1 : 1;
		}

		void next() {
			bool f = false;
			if (!last) {
				for (int i = 1; i < n; i++) {
					if (p[i - 1] < p[i]) {
						f = true;
						break;
					}
				}
				if (!f) {
					last = true;
					return;
				}
			}
			else {
				return;
			}
			int* b = new int[n];
			for (int i = n - 1; i > 0; i--) {
				if (p[i] > p[i - 1]) {
					int im = i;
					for (int j = i + 1; j < n; j++) {
						if (p[im] > p[j] && p[j] > p[i - 1]) {
							im = j;
						}
					}
					swap(p[i - 1], p[im]);
					for (int j = i; j < n; j++) {
						b[j] = p[j];
					}
					for (int j = i; j < n; j++) {
						p[j] = b[n + i - j - 1];
					}
					break;
				}
			}
			delete b;
		}

		bool isLast() {
			return last;
		}

	private:
		int n;
		bool last;
		std::vector <int> p;
};

Vec4::Vec4(){
	for (int i = 0; i < v_N; i++) {
		coord[i] = 0;
	}
}

Vec4::Vec4(float a[v_N]) {
	for (int i = 0; i < v_N; i++) {
		coord[i] = a[i];
	}
}

Vec4::Vec4(float x, float y, float z, float t) {
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
	coord[3] = t;
}

Vec4::Vec4(Vec4 &x) {
	for (int i = 0; i < v_N; i++) {
		coord[i] = x.coord[i];
	}
}


float& Vec4::x() { 
	return (coord[0]);
}

float& Vec4::y() {
	return coord[1];
}

float& Vec4::z() {
	return coord[2];
}

float& Vec4::w() {
	return coord[3];
}

float& Vec4::operator[](int i) {
	if (i < v_N) {
		return coord[i];
	}
	else {

	}
}
/*
Vec4 Vec4::operator=(Vec4 &x){
	return Vec4(x);
}
*/
Vec4 Vec4::operator-(Vec4 &x) {
	Vec4 y(x);
	for (int i = 0; i < v_N; i++) {
		y.coord[i] = -x.coord[i];
	}
	return y;
}

Vec4 operator+(const Vec4 &l, const Vec4 &r){
	Vec4 t;
	for (int i = 0; i < v_N; i++){
		
		t.coord[i] = l.coord[i] + r.coord[i];
	}
	return t;
}

Vec4 operator-(const Vec4 &l, const Vec4 &r){
	Vec4 t;
	for (int i = 0; i < v_N; i++){
		t.coord[i] = l.coord[i] - r.coord[i];
	}
	return t;
}

float operator*(const Vec4 &l, const Vec4 &r) {
	float t = 0.0f;
	for (int i = 0; i < v_N; i++) {
		t += l.coord[i] * r.coord[i];
	}
	return t;
}

Vec4 operator*(const float &l, const Vec4 &r) {
	Vec4 t;
	for (int i = 0; i < v_N; i++) {
		t.coord[i] = l * r.coord[i];
	}
	return t;
}


float Vec4::len(){
	float l = 0.0f;
	for (int i = 0; i < v_N; i++) {
		l += coord[i] * coord[i];
	}
	return sqrt(l);
}

Vec4 operator^(const Vec4 &l, const Vec4 &r) {
	float x = l.coord[1] * r.coord[2] - l.coord[2] * r.coord[1];
	float y = l.coord[2] * r.coord[0] - l.coord[0] * r.coord[2];
	float z = l.coord[0] * r.coord[1] - l.coord[1] * r.coord[0];
	return Vec4(x, y, z, 0);
}

Vec4& Vec4::normalize(){
	float t = 0;
	for (int i = 0; i < v_N; i++){
		t += coord[i] * coord[i];
	}
	t = sqrt(t);
	for (int i = 0; i < v_N; i++){
		coord[i] /= t;
	}
	return *this;
}


float* Vec4::getArray() {
	return coord;
}

Mat4::Mat4() {
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			vecs[i][j] = 0;
		}
	}
}

Mat4::Mat4(float a[v_N * v_N]) {
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			vecs[i][j] = a[i * v_N + j];
		}
	}
}

Mat4::Mat4(Vec4 v[v_N]) {
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			vecs[i][j] = v[i][j];
		}
	}
}

float* Mat4::operator[](int i) {
	return vecs[i];
}

Mat4 Mat4::operator-() {
	Mat4 t;
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			t.vecs[i][j] = -vecs[i][j];
		}
	}
	return t;
}

Mat4 Mat4::operator=(Mat4 &x) {
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			vecs[i][j] = x.vecs[i][j];
		}
	}
	return *this;
}


Vec4 Mat4::operator()(Vec4 &x) {
	float r[v_N] = {0, 0, 0, 0};
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			r[i] += x[j] * vecs[i][j];
		}
	}
	return Vec4(r);
}

Mat4 operator+(const Mat4 &l, const Mat4&r) {
	Mat4 t;
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			t.vecs[i][j] = l.vecs[i][j] + r.vecs[i][j];
		}
	}
	return t;
}

Mat4 operator-(const Mat4 &l, const Mat4&r) {
	Mat4 t;
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			t.vecs[i][j] = l.vecs[i][j] - r.vecs[i][j];
		}
	}
	return t;
}

Mat4 operator*(const Mat4 &l, const Mat4 &r) {
	Mat4 t;
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			for (int k = 0; k < v_N; k++) {
				t.vecs[i][j] += l.vecs[i][k] * r.vecs[k][j];
			}
		}
	}
	return t;
}

Mat4 operator*(const float &l, const Mat4 &r) {
	Mat4 t;
	for (int i = 0; i < v_N; i++) {
		for (int j = 0; j < v_N; j++) {
			t.vecs[i][j] += l * r.vecs[j][i];
		}
	}
	return t;
}

float Mat4::det() {
	Permut p(v_N);
	float d = 0;
	std::vector <int> a;
	while (!p.isLast()) {
		a = p.get();
		float m = 1;
		for (int i = 0; i < v_N; i++) {
			m *= vecs[i][a[i]];
		}
		m *= p.pairityCof();
		d += m;
		p.next();
	}
	return d;
}

void Mat4::transpose() {
	for (int i = 1; i < v_N - 1; i++) {
		for (int j = i; j < v_N - 1; j++) {
			swap(vecs[i][j], vecs[j][i]);
		}
	}
}


float* Mat4::getArray() {
	return (float*)vecs;
}

Mat4 I() {
	float a[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return Mat4(a);
}

Mat4 translate(const Mat4& m, Vec4& v) {
	float x = v.x();
	float y = v.y();
	float z = v.z();
	float a[] = {
		0.0f, 0.0f, 0.0f, x,
		0.0f, 0.0f, 0.0f, y,
		0.0f, 0.0f, 0.0f, z,
		0.0f, 0.0f, 0.0f, 0.0f
	};
	return Mat4(a) + m;
}

Mat4 rotate(const Mat4& m, Vec4& v, const float angle) {
	Vec4 a[4];
	for (int i = 0; i < 3; i++) {
		if (v[i] != 0.0f) {
			a[i][i] = 1.0f;
		}
		else {
			a[i][i] = cos(angle);
			for (int j = i; j < 3; j++) {
				if (v[j] == 0.0f) {
					a[i][j] = sin(angle);
					a[j][i] = -sin(angle);
				}
			}
		}
	}
	a[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return Mat4((float*)a);
}

Mat4 scale(const Mat4& m, Vec4& v) {
	float x = v.x();
	float y = v.y();
	float z = v.z();
	float a[] = {
		x,    0.0f, 0.0f, 0.0f,
		0.0f, y,    0.0f, 0.0f,
		0.0f, 0.0f, z,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return Mat4(a);
}

float nLbd(const float a, const float b) {
	return (a + b) / (a - b);
}

float dnLbd(const float a, const float b) {
	return 2.0f / (a - b);
}

float dnnLbd(const float c, const float a, const float b) {
	return 2.0f * c / (a - b);
}

Mat4 ortho(float l, float r, float t, float b, float n, float f){
	Mat4 a;
	a = scale(a, Vec4(dnLbd(r, l), dnLbd(t, b), -dnLbd(f, n), 1.0f));
	a = translate(a, Vec4(-nLbd(r, l), -nLbd(t, b), -nLbd(f, n), 1.0f));
	return a;
}

Mat4 frustum(float l, float r, float t, float b, float n, float f) {
	float a[] = {
		dnnLbd(n, r, l), 0.0f,             nLbd(r, l), 0.0f,
		0.0f,            dnnLbd(n, t, b),  nLbd(t, b), 0.0f,
		0.0f,            0.0f,            -nLbd(f, n), dnnLbd(n*f, f, n),
		0.0f,            0.0f,            -1.0f,       0.0f
	};
	return Mat4(a);
}

Mat4 perspective(const float fovy, const float ar, const float n, const float f) {
	float t = n * tan(M_PI * fovy / 360);
	float b = -t;
	float r = t * ar;
	float l = -r;
	return frustum(l, r, t, b, n, f);
}