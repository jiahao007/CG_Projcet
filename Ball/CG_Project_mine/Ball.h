#pragma once
#ifndef BALL_H_
#define BALL_H_
#include<gl/glut.h>

enum Material{WOOD,PAPER,STONE};
extern GLuint textures[56];
class Ball
{
private:
	GLfloat radius;
	GLfloat speed;
	GLfloat acceleration;
	GLfloat angle;
	GLfloat direction;
	GLfloat eye[3];
	GLfloat center[3];
	GLfloat rotate_Vector[3];
	GLfloat forward_Vector[3];
	GLint   deadTime;
	
	Material material;

	//GLfloat rectangle_x[10][4];
	//GLfloat rectangle_y[10][4];

	GLfloat forwardSpeed;
	GLfloat LeftSpeed;
public:
	Ball();
	
	GLfloat Get_Radius();
	GLfloat Get_Speed();
	GLfloat Get_Accleration();
	GLfloat Get_Angle();
	GLfloat Get_Eye(int i);
	GLfloat Get_Center(int i);
	GLfloat Get_Rotate_Vector(int i);
	GLfloat Get_Direction();
	//GLfloat Get_Material();

	void Set_Radius(GLfloat radius);
	void Set_Speed(GLfloat speed);
	void Set_Acceleration(GLfloat acceleration);
	void Set_Angle(GLfloat angle);
	void Set_Eye(GLfloat* eye);
	void Set_Center(GLfloat* center);
	void Set_Rotate_Vector(GLfloat* forward_Vector);
	void Set_Material();

	void mul();

	void Left();
	void Right();
	void Back();
	void Forward();
	void Stop();

	void Friction();

	void Roll();
};
#endif


