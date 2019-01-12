#include <stdio.h>
#include<vector>
#include"point.h"
#include <GL\glut.h>
using namespace std;
class element {
public:
	element();
	element(double x, double y, double z);
	double getx();
	double gety();
	double getz();
	void moveto(double x, double y, double z);
	void setx(double nx);
	void sety(double ny);
	void setz(double nz);
private:
	double x;
	double y;
	double z;
};
class glassRectangle : public element {
public:
	glassRectangle();
	glassRectangle(double x, double y, double z, double A = 300, double B = 100, double C = 20,
		double vx = 0, double vy = 0);
	void Draw(GLfloat *color, GLfloat boundX, GLfloat boundY);
	void Break(GLfloat HitPointX, GLfloat HitPointY, float t0, float t);
	double geta() { return a; }
	double getb() { return b; }
	double getc() { return c; }
private:
	double a;
	double b;
	double c;
	double vx, vy;
};

class patch {
public:
	patch(vector<point> Pset, GLfloat vx, GLfloat vy, GLfloat vz);
	void Draw(GLfloat x, GLfloat y, GLfloat z, GLfloat c, int t);
private:
	vector<point> Vertex;
	GLfloat vx;
	GLfloat vy;
	GLfloat vz;
};