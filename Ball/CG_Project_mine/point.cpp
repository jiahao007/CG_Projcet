#include <iostream>
#include <string>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\glut.h>
#include <math.h>
#include <Windows.h>
#include "point.h"
using namespace std;

point::point(GLfloat X, GLfloat Y)
{
	x = X;
	y = Y;
}
void point::print()
{
	printf("(%lf,%lf) ", x, y);
}

point::point(GLfloat X, GLfloat Y, GLfloat Z)
{
	x = X;
	y = Y;
	z = Z;
}

GLfloat Dot(point a, point b)
{
	return a.getx() * b.getx() + a.gety() * b.gety() + a.getz() * b.getz();
}

point Cross(point a, point b)
{
	point Point((a.gety() * b.getz() - a.getz() * b.gety()) / 100.0,
		(a.getz() * b.getx() - a.getx() * b.getz()) / 100.0,
		(a.getx() * b.gety() - a.gety() * b.getx()) / 100.0);
	return Point;
}

point Normalize(point N)
{
	GLfloat absN = pow((N.getx() * N.getx() + N.gety() * N.gety() + N.getz() * N.getz()), 0.5);
	point Point(N.getx() / absN, N.gety() / absN, N.getz() / absN);
	return Point;
}
