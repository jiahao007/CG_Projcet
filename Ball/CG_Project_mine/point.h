#pragma once
#include <iostream>
#include <string>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\glut.h>
#include <math.h>
#include <Windows.h>

class point {
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
public:
	point() {};
	point(GLfloat X, GLfloat Y);
	point(GLfloat X, GLfloat Y, GLfloat Z);
	void print();
	GLfloat getx() {
		return x;
	};
	GLfloat gety() {
		return y;
	};
	GLfloat getz() {
		return z;
	}
	void setx(GLfloat x) {
		x = x;
	}
	void sety(GLfloat y) {
		y = y;
	}
	void setz(GLfloat z) {
		z = z;
	}
};

GLfloat Dot(point a, point b);
point Cross(point a, point b);
point Normalize(point N);