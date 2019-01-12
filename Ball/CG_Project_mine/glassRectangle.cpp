#include "glassRectangle.h"
#include "point.h"
#include <vector>
#include <ctime>
using namespace std;
#define PI 3.14
#define G 9.8
element::element()
{
	x = 0;
	y = 0;
	z = 0;
}
element::element(double X, double Y, double Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
}
double element::getx()
{
	return x;
}
double element::gety()
{
	return y;
}
double element::getz()
{
	return z;
}
void element::moveto(double nx, double ny, double nz)
{
	x = nx;
	y = ny;
	z = nz;
}
void element::setx(double nx)
{
	x = nx;
}
void element::sety(double ny)
{
	y = ny;
}
void element::setz(double nz)
{
	z = nz;
}
glassRectangle::glassRectangle() :element()
{
	a = 20;
	b = 10;
	c = 5;
	vx = vy = 0;
}
glassRectangle::glassRectangle(double x, double y, double z, double A, double B, double C,
	double vx, double vy) :element(x, y, z)
{
	a = A;
	b = B;
	c = C;
	this->vx = vx;
	this->vy = vy;
}

void glassRectangle::Draw(GLfloat *color, GLfloat boundX, GLfloat boundY){
	GLfloat x, y, z;
	x = this->getx();
	y = this->gety();
	z = this->getz();
	if ((vx > 0 && x + a / 2 >= boundX) || (vx<0 && x - a / 2 <= -boundX))
		vx = -vx;
	if ((vx > 0 && x + a / 2 >= boundY) || (vy<0 && y - a / 2 <= -boundY))
		vy = -vy;
	x = x + vx;
	y = y + vy;
	this->moveto(x, y, z);
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 0.2 };
	GLfloat lightPosition[] = { x - 2.0, y, z, 1 };

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightSpecular);

	glEnable(GL_BLEND);        //启用混合状态
	glEnable(GL_LIGHTING);        //启用光照
	glEnable(GL_LIGHT1);        //打开光源1
	glEnable(GL_DEPTH_TEST);    //启用深度检测
	glEnable(GL_COLOR_MATERIAL);//材质跟踪当前绘图色
	glTranslatef(x, y, z);
	glColor4f(color[0], color[1], color[2], color[3]);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);   //front
	glVertex3f(b / 2, -a / 2, c / 2);
	glVertex3f(b / 2, a / 2, c / 2);
	glVertex3f(b / 2, a / 2, -c / 2);
	glVertex3f(b / 2, -a / 2, -c / 2);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);   //back
	glVertex3f(-b / 2, -a / 2, c / 2);
	glVertex3f(-b / 2, a / 2, c / 2);
	glVertex3f(-b / 2, a / 2, -c / 2);
	glVertex3f(-b / 2, -a / 2, -c / 2);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);   //left
	glVertex3f(-b / 2, -a / 2, c / 2);
	glVertex3f(b / 2, -a / 2, c / 2);
	glVertex3f(b / 2, -a / 2, -c / 2);
	glVertex3f(-b / 2, -a / 2, -c / 2);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);   //right
	glVertex3f(-b / 2, a / 2, c / 2);
	glVertex3f(b / 2, a / 2, c / 2);
	glVertex3f(b / 2, a / 2, -c / 2);
	glVertex3f(-b / 2, a / 2, -c / 2);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);   //up
	glVertex3f(-b / 2, -a / 2, c / 2);
	glVertex3f(-b / 2, a / 2, c / 2);
	glVertex3f(b / 2, a / 2, c / 2);
	glVertex3f(b / 2, -a / 2, c / 2);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);   //down
	glVertex3f(-b / 2, -a / 2, -c / 2);
	glVertex3f(-b / 2, a / 2, -c / 2);
	glVertex3f(b / 2, a / 2, -c / 2);
	glVertex3f(b / 2, -a / 2, -c / 2);
	glEnd();
	glTranslatef(-x, -y, -z);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);        //启用光照
	glDisable(GL_LIGHT1);        //打开光源1
	glDisable(GL_DEPTH_TEST);    //启用深度检测
	glDisable(GL_COLOR_MATERIAL);//材质跟踪当前绘图色
}

void glassRectangle::Break(GLfloat HitPointX, GLfloat HitPointY, float t0, float t){
	//printf("to:%lf,t:%lf\n", t0, t);
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightPosition[] = { 0.5, 0.5, 4.0, 0.0 };
	float time = t - t0;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

	GLfloat color[4] = { 0.0,1.0,1.0,0.3 };
	glColor4f(color[0], color[1], color[2], color[3]);
	

	glEnable(GL_BLEND);        //启用混合状态
	glEnable(GL_LIGHTING);        //启用光照
	glEnable(GL_LIGHT1);        //打开光源1
	glEnable(GL_DEPTH_TEST);    //启用深度检测
	glEnable(GL_COLOR_MATERIAL);//材质跟踪当前绘图色
	glTranslatef(getx(), gety(), getz());

	//左上角quad
	glPushMatrix();
	glTranslatef(-0.5*time, -2.6*time, -G*time*time);
	//glRotatef(time, a / 2, b / 6, c / 2);
	glScalef(t0 / t, t0 / t, t0 / t);
	glBegin(GL_QUADS);
	glVertex3f(b / 2, -a / 2, c / 6);
	glVertex3f(b / 2, -a / 2, c / 2);
	glVertex3f(b / 2, -a / 6, c / 2);
	glVertex3f(b / 2, HitPointX, HitPointY);
	glEnd();
	glPopMatrix();

	//正上方triangle
	glPushMatrix();
	glTranslatef(-0.8*time, -0.1*time*time, -G*time*time);
	//glRotatef(2*time, -a / 2, b / 6/, c / 2);
	glScalef(t0 / t, t0 / t, t0 / t);
	glBegin(GL_TRIANGLES);
	glVertex3f(b / 2, -a / 6, c / 2);
	glVertex3f(b / 2, a / 6, c / 2);
	glVertex3f(b / 2, HitPointX, HitPointY);
	glEnd();
	glPopMatrix();
	
	//右上方quad
	glPushMatrix();
	glTranslatef(-0.5*time, 1.6*time, -G*time*time);
	//glRotatef(time, a / 2, b / 6, c / 2);
	glScalef(t0 / t, t0 / t, t0 / t);
	glBegin(GL_QUADS);
	glVertex3f(b / 2, a / 6, c / 2);
	glVertex3f(b / 2, a / 2, c / 2);
	glVertex3f(b / 2, a / 2, c / 6);
	glVertex3f(b / 2, HitPointX, HitPointY);
	glEnd();
	glPopMatrix();
	
	//右tri
	glPushMatrix();
	glTranslatef(-0.5*time, 3.1*time, -G*time*time);
	glRotatef(2 * time, a / 2, -b / 6, 0);
	glScalef(t0 / t, t0 / t, t0 / t);
	glBegin(GL_TRIANGLES);
	glVertex3f(b / 2, a / 2, c / 6);
	glVertex3f(b / 2, a / 2, -c / 6);
	glVertex3f(b / 2, HitPointX, HitPointY);
	glEnd();
	glPopMatrix();

	//右下方quad
	glPushMatrix();
	glTranslatef(-0.5*time, 3.6*time, -G*time*(time+0.5));
	//glRotatef(time, a / 2, b / 6, c / 2);
	glScalef(t0 / t, t0 / t, t0 / t);
	glBegin(GL_QUADS);
	glVertex3f(b / 2, a / 2, -c / 6);
	glVertex3f(b / 2, a / 2, -c / 2);
	glVertex3f(b / 2, a / 6, -c / 2);
	glVertex3f(b / 2, HitPointX, HitPointY);
	glEnd();
	glPopMatrix();

	//下方tri
	glPushMatrix();
	glTranslatef(-0.5*time, 0.1*time*time, -G*time*(time+0.6));
	//glRotatef(2*time, -a / 2, b / 6, c / 2);
	glScalef(t0 / t, t0 / t, t0 / t);
	glBegin(GL_TRIANGLES);
	glVertex3f(b / 2, -a / 6, -c / 2);
	glVertex3f(b / 2, a / 6, -c / 2);
	glVertex3f(b / 2, HitPointX, HitPointY);
	glEnd();
	glPopMatrix();

	//左下方quad
	glPushMatrix();
	glTranslatef(-0.5*time, -3.6*time, -G*time*(time + 0.5));
	//glRotatef(time, a / 2, b / 6, c / 2);
	glScalef(t0 / t, t0 / t, t0 / t);
	glBegin(GL_QUADS);
	glVertex3f(b / 2, -a / 6, -c / 2);
	glVertex3f(b / 2, -a / 2, -c / 2);
	glVertex3f(b / 2, -a / 2, -c / 6);
	glVertex3f(b / 2, HitPointX, HitPointY);
	glEnd();
	glPopMatrix();
	
	//左边tri
	glPushMatrix();
	glTranslatef(-0.5*time, -3.6*time, -G*time*(time + 0.3));
	//glRotatef(2*time, -a / 2, b / 6, c / 2);
	glScalef(t0 / t, t0 / t, t0 / t);
	glBegin(GL_TRIANGLES);
	glVertex3f(b / 2, -a / 2, -c / 6);
	glVertex3f(b / 2, -a / 2, c / 6);
	glVertex3f(b / 2, HitPointX, HitPointY);
	glEnd();
	glPopMatrix();
	
	glTranslatef(-getx(), -gety(), -getz());
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);        //启用光照
	glDisable(GL_LIGHT1);        //打开光源0
	glDisable(GL_DEPTH_TEST);    //启用深度检测
	glDisable(GL_COLOR_MATERIAL);//材质跟踪当前绘图色

}


patch::patch(vector<point> Pset, GLfloat vx, GLfloat vy, GLfloat vz)
{
	for (int i = 0; i < Pset.size(); i++)
	{
		Vertex.push_back(Pset[i]);
	}
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
}

void patch::Draw(GLfloat x, GLfloat y, GLfloat z, GLfloat c, int t){
	glutWireCube(1);
	glColor4f(0.0, 1.0, 1.0, 0.5);
	int r = rand() % 2;
	glPushMatrix();
	glTranslatef(x + vx * t, y + vy * t - 0.5*G*(t)*(t), z + vz * t);  //move
	//glRotatef(t, Vertex[0].getx(), Vertex[0].gety(), 0);  //rotate around itself
	glBegin(GL_POLYGON); //front
	for (int i = 0; i < Vertex.size(); i++)
	{
		glVertex3f(Vertex[i].getx(), Vertex[i].gety(), c / 2);
	}
	glEnd();

	glBegin(GL_POLYGON); //back
	for (int i = 0; i < Vertex.size(); i++)
	{
		glVertex3f(Vertex[i].getx(), Vertex[i].gety(), -c / 2);
	}
	glEnd();

	glBegin(GL_QUADS);//round
	for (int i = 0; i < Vertex.size() - 1; i++)
	{
		glVertex3f(Vertex[i].getx(), Vertex[i].gety(), c / 2);
		glVertex3f(Vertex[i].getx(), Vertex[i].gety(), -c / 2);
		glVertex3f(Vertex[i + 1].getx(), Vertex[i + 1].gety(), -c / 2);
		glVertex3f(Vertex[i + 1].getx(), Vertex[i + 1].gety(), c / 2);
	}
	glEnd();
	glPopMatrix();
	
}