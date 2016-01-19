#pragma once
#define v_N 4

#include <vector>

class Vec4 {
	public:
		Vec4();
		Vec4(float a[v_N]);
		Vec4(float x, float y, float z, float t);
		Vec4(Vec4 &x);
		float& operator[](int i);
		Vec4 operator-(Vec4 &x);
		//Vec4 operator=(Vec4 &x);
		float& x();
		float& y();
		float& z();
		float& w();
		friend Vec4 operator+(const Vec4 &l, const Vec4 &r);
		friend Vec4 operator-(const Vec4 &l, const Vec4 &r);
		friend Vec4 operator*(const float &l, const Vec4 &r);
		friend float operator*(const Vec4 &l, const Vec4 &r);
		friend Vec4 operator^(const Vec4 &l, const Vec4 &r);
		float len();
		Vec4& normalize();
		float* getArray();
	private:
		float coord[v_N];
		bool Tflag;
};

class Mat4{
	public:
		Mat4();
		Mat4(float a[v_N * v_N]);
		Mat4(Vec4 v[v_N]);
		float* operator[](int i);
		Mat4 operator-();
		Mat4 operator=(Mat4 &x);
		Vec4 operator()(Vec4 &x);
		friend Mat4 operator+(const Mat4 &l, const Mat4 &r);
		friend Mat4 operator-(const Mat4 &l, const Mat4 &r);
		friend Mat4 operator*(const Mat4 &l, const Mat4 &r);
		friend Mat4 operator*(const float &l, const Mat4 &r);
		float det();
		void transpose();
		float* getArray();
	private:
		float vecs[v_N][v_N];
		bool Tflag;
};

Mat4 I();
Mat4 translate(const Mat4& m, Vec4& v);
Mat4 rotate(const Mat4& m, Vec4& v, const float angle);
Mat4 scale(const Mat4& m, Vec4& v);
Mat4 ortho(float left, float right, float top, float bottom, float near, float far);
Mat4 frustum(float left, float right, float top, float bottom, float near, float far);
Mat4 perspective(const float fovy, float ar, float near, float far);