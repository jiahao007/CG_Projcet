#include"Ball.h"
#include<math.h>
#include<iostream>
#define THRESHHOLD 0.1
#define VELOCITY_LIMIT 0.1
#define NUM_RECTANGLE 24
// rectangle
//GLfloat rectangle_x[NUM_RECTANGLE][4] = { {56.96,57.89,60.14,59.18},{57.89,58.22,60.72,60.14},{58.54,60.5,60,58.44} };
//GLfloat rectangle_y[NUM_RECTANGLE][4] = { {-9.74,-5.18,-4.58,-10.14},{-5.18,2.26,2.66,-4.58},{-0.66,-0.36,1.92,1.42}};
GLfloat rectangle_x[NUM_RECTANGLE][4] = { {56.96,58.48,60.26,58.96},{58.48,58.46,60.42,60.26},{58.54,58,60,60.42} ,{58,57.22 ,58.92 , 60},{57.22,55.96,57.02,58.92},{55.96,54.4,54.5,57.02},{54.4,53.16,51.8, 54.5},{53.16,52.1 ,50.34,51.8},{52.1,51.52,49.4 ,50.34},{51.52,49.36 ,47.62 ,49.4},{49.36,48.48,46.63,47.62},{48.48,48.65,45.51,46.63},{48.65,44.32,43.78,45.51},{44.32,39.58,40.3 ,43.78},{39.58,37.28,38.54,40.3 },{37.28,35.62,37.36,38.54},{35.62,34.22,36.1,37.36} ,{34.22,33.04,35.12,36.1},{33.04,31.42,33.56,35.12},{31.42,30.88,32.6,33.56},{30.88,30.08,29.78,32.6}, {30.08,28.56,27.4,29.78},{28.56,17.42,15.66,27.4},{17.42,11.32,10.82,15.66} };
GLfloat rectangle_y[NUM_RECTANGLE][4] = { {-9.74,-2.22,-3.55,-10.18},{-2.22,2.4,2.54,-3.55},{2.4,4.4,4.92,2.54}, {4.4 ,6.02,7.06 ,4.92}, {6.02, 7.10 , 8.76,7.06}  ,{7.10, 7.54, 9.5 ,8.76},{7.54, 7.18,8.74, 9.5 },{7.18 ,5.68 ,6.74 ,8.74},{5.68, 3.8 ,4.04 ,6.74} ,{3.8  ,-4.48 ,-3.54 ,4.04},{-4.48,-6.36,-5.2 ,-3.54},{-6.36, -8.1,-6.35, -5.2},{-8.1, -9.08,-7.06,-6.35},{-9.08,-9.06,-6.92,-7.06},{-9.06,-7.88,-6.18,-6.92},{-7.88,-6.16,-4.84,-6.18},{-6.16,-4.14,-3.14,-4.84},{-4.14,-0.1 ,0.6,-3.14}, {-0.1 ,10.56,11.0 ,0.6 }, {10.56,12.24,13.36,11.0},{12.24,12.52,14.56,13.36},{12.52,11.74,13.5,14.56},{11.74,2.38,3.98,13.5}, {2.38,-1.2,0.86,3.98} };


float GetCross(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x, GLfloat y)
{
	return (x2 - x1)*(y - y1) - (x - x1)*(y2 - y1);
}

bool JudgeInside(GLfloat x, GLfloat y)
{
	int flag = 0;
	for (int i = 0; i < NUM_RECTANGLE; i++)
	{
		GLfloat p1_x = rectangle_x[i][0];
		GLfloat p1_y = rectangle_y[i][0];
		GLfloat p2_x = rectangle_x[i][1];
		GLfloat p2_y = rectangle_y[i][1];
		GLfloat p3_x = rectangle_x[i][2];
		GLfloat p3_y = rectangle_y[i][2];
		GLfloat p4_x = rectangle_x[i][3];
		GLfloat p4_y = rectangle_y[i][3];
		if (GetCross(p1_x, p1_y, p2_x, p2_y, x, y)*GetCross(p3_x, p3_y, p4_x, p4_y, x, y) >= 0 && GetCross(p2_x, p2_y, p3_x, p3_y, x, y)*GetCross(p4_x, p4_y, p1_x, p1_y, x, y) >= 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}

Ball::Ball()
{
	radius = 0.15;
	speed = 0;
	acceleration = 0.02;
	angle = 0;
	material = PAPER;

	eye[0] = 5;
	eye[1] = 0;
	eye[2] = 0;

	center[0] = 58;
	center[1] = -9.5;
	center[2] = -5.63;

	rotate_Vector[0] = 0;
	rotate_Vector[1] = 0;
	rotate_Vector[2] = 0;

	forward_Vector[0] = 0;
	forward_Vector[1] = 0;
	forward_Vector[2] = 0;

	forwardSpeed = 0;
	LeftSpeed = 0;

	
} 

GLfloat Ball::Get_Radius()
{
	return radius;
}

GLfloat Ball::Get_Speed()
{
	return speed;
}

GLfloat Ball::Get_Accleration()
{
	return acceleration;
}

GLfloat Ball::Get_Angle()
{
	return angle;
}

GLfloat Ball::Get_Center(int i)
{
	return center[i];
}

GLfloat Ball::Get_Eye(int i)
{
	return eye[i];
}

GLfloat Ball::Get_Rotate_Vector(int i)
{
	return rotate_Vector[i];
}

GLfloat Ball::Get_Direction()
{
	direction = atan2(rotate_Vector[2], rotate_Vector[0]);
	return direction;
}

void Ball::Set_Radius(GLfloat radius)
{
	this->radius = radius;
}

void Ball::Set_Speed(GLfloat speed)
{
	this->speed = speed;
}

void Ball::Set_Acceleration(GLfloat acceleration)
{
	this->acceleration = acceleration;
}

void Ball::Set_Angle(GLfloat angle)
{
	this->angle = angle;
}

void Ball::Set_Eye(GLfloat * eye)
{
	this->eye[0] = eye[0];
	this->eye[1] = eye[1];
	this->eye[2] = eye[2];
}

void Ball::Set_Center(GLfloat * center)
{
	this->center[0] = center[0];
	this->center[1] = center[1];
	this->center[2] = center[2];
}

void Ball::Set_Rotate_Vector(GLfloat * rotate_Vector)
{
	this->rotate_Vector[0] = rotate_Vector[0];
	this->rotate_Vector[1] = rotate_Vector[1];
	this->rotate_Vector[2] = rotate_Vector[2];
}

void Ball::Set_Material()
{
	Material material = this->material;
	
	if (material == PAPER) {
		this->material = STONE;
	}

	if (material == STONE) {
		this->material = WOOD;
	}

	if (material == WOOD) {
		this->material = PAPER;
	}
}


void Ball::mul()
{
	/*forward_Vector[0] = -rotate_Vector[1];
	forward_Vector[1] = -rotate_Vector[0];
	forward_Vector[2] = 0;*/
	rotate_Vector[0] = -forward_Vector[1];
	rotate_Vector[1] = -forward_Vector[0];
}

void Ball::Left()
{
	//// 改变旋转方向
	//if (this->rotate_Vector[1] <= THRESHHOLD&&this->rotate_Vector[1] >= -THRESHHOLD)
	//{
	//	//this->rotate_Vector[0] = 0;
	//}
	//else
	//{
	//	if (this->rotate_Vector[1] > THRESHHOLD)
	//		this->rotate_Vector[1] -= THRESHHOLD;
	//	else
	//		this->rotate_Vector[1] += THRESHHOLD;
	//}
	////this->rotate_Vector[0] = 1;

	//if (this->rotate_Vector[0] > 1)
	//{
	//	this->rotate_Vector[0] = 1;
	//}
	//else
	//	this->rotate_Vector[0] += THRESHHOLD;

	//// 改变速度
	//if (this->speed < -VELOCITY_LIMIT)
	//{
	//	this->speed = -VELOCITY_LIMIT;
	//}
	//else
	//{
	//	this->speed -= acceleration;
	//}
	if (this->LeftSpeed > VELOCITY_LIMIT) {
		this->LeftSpeed = VELOCITY_LIMIT;
	}
	else {
		this->LeftSpeed += acceleration;
	}
}

void Ball::Right()
{
	//// 改变旋转方向
	//if (this->rotate_Vector[1] <= THRESHHOLD && this->rotate_Vector[1] >= -THRESHHOLD)
	//{
	//	//this->rotate_Vector[0] = 0;
	//}
	//else
	//{
	//	if (this->rotate_Vector[1] > THRESHHOLD)
	//		this->rotate_Vector[1] -= THRESHHOLD;
	//	else
	//		this->rotate_Vector[1] += THRESHHOLD;
	//}

	////this->rotate_Vector[0] = 1;
	//if (this->rotate_Vector[0] < -1)
	//{
	//	this->rotate_Vector[0] = -1;
	//}
	//else
	//	this->rotate_Vector[0] -= THRESHHOLD;

	//// 改变速度
	//if (this->speed > VELOCITY_LIMIT)
	//{
	//	this->speed = VELOCITY_LIMIT;
	//}
	//else
	//{
	//	this->speed += acceleration;
	//}
	if (this->LeftSpeed < -VELOCITY_LIMIT) {
		this->LeftSpeed = -VELOCITY_LIMIT;
	}
	else {
		this->LeftSpeed -= acceleration;
	}
}

void Ball::Forward()
{
	//if (this->rotate_Vector[0]<=THRESHHOLD&&this->rotate_Vector[0]>=-THRESHHOLD)
	//{
	//	
	//}
	//else
	//{
	//	if (this->rotate_Vector[0] > THRESHHOLD )
	//		this->rotate_Vector[0] -= THRESHHOLD;
	//	else
	//		this->rotate_Vector[0] += THRESHHOLD;
	//}

	//
	//if (this->rotate_Vector[1] < -1)
	//	this->rotate_Vector[1] = -1;
	//else
	//	this->rotate_Vector[1] -= THRESHHOLD;


	//// 改变速度
	//if (this->speed > VELOCITY_LIMIT)
	//{
	//	this->speed = VELOCITY_LIMIT;
	//}
	//else
	//{
	//	this->speed += acceleration;
	//}
	if (this->forwardSpeed > VELOCITY_LIMIT) {
		this->forwardSpeed = VELOCITY_LIMIT;
	}
	else {
		this->forwardSpeed += acceleration;
	}
}

void Ball::Back()
{
	//if (this->rotate_Vector[0] <= THRESHHOLD && this->rotate_Vector[0] >= -THRESHHOLD)
	//{
	//	//this->rotate_Vector[2] = 0;
	//}
	//else
	//{
	//	if (this->rotate_Vector[0] > THRESHHOLD)
	//		this->rotate_Vector[0] -= THRESHHOLD;
	//	else
	//		this->rotate_Vector[0] += THRESHHOLD;
	//}

	////this->rotate_Vector[1] = 1;
	//if (this->rotate_Vector[1] > 1)
	//	this->rotate_Vector[1] = 1;
	//else
	//	this->rotate_Vector[1] += THRESHHOLD;

	//// 改变速度
	//if (this->speed < -VELOCITY_LIMIT)
	//{
	//	this->speed = -VELOCITY_LIMIT;
	//}
	//else
	//{
	//	this->speed -= acceleration;
	//}
	if (this->forwardSpeed < -VELOCITY_LIMIT) {
		this->forwardSpeed = -VELOCITY_LIMIT;
	}
	else {
		this->forwardSpeed -= acceleration;
	}
}

void Ball::Stop()
{
	this->forwardSpeed = 0;
	this->LeftSpeed = 0;
}

void Ball::Friction() 
{
	/*if (speed != 0) {
		if (this->forwardSpeed > 0 && this->LeftSpeed != 0) {
			this->forwardSpeed -= 0.002 * speed / fabsf(this->LeftSpeed);
		}
		if (this->forwardSpeed < 0 && this->LeftSpeed != 0) {
			this->forwardSpeed += 0.002 * speed / fabsf(this->LeftSpeed);
		}

		if (this->LeftSpeed > 0 && this->forwardSpeed != 0) {
			this->LeftSpeed -= 0.002 * speed / fabsf(this->forwardSpeed);;
		}
		if (this->LeftSpeed < 0 && this->forwardSpeed != 0) {
			this->LeftSpeed += 0.002 * speed / fabsf(this->forwardSpeed);;
		}
	}*/
	
}

void Ball::Roll()
{
	
	glPushMatrix();

	Friction();

	this->forward_Vector[0] = this->forwardSpeed;
	this->forward_Vector[1] = this->LeftSpeed;

	mul();
	//direction = Get_Direction();
	//forward_Vector[0] = 1;

	if (angle > 360)
		angle = 0;
	speed = sqrt(this->forwardSpeed * this->forwardSpeed + this->LeftSpeed * this->LeftSpeed);
	angle += fabsf(speed) * 90;
	//glTranslatef(center[0] + fabsf(speed) * forward_Vector[0], center[1] + fabsf(speed) * forward_Vector[1], center[2] + fabsf(speed) * forward_Vector[2]);
	//glTranslatef(center[0] + speed * forward_Vector[0] , center[1] + speed*forward_Vector[1], center[2] + speed * forward_Vector[2]);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[(int)material]);


	glTranslatef(center[0], center[1], center[2]);
	
	glRotatef(angle, -rotate_Vector[0], -rotate_Vector[1], rotate_Vector[2]);

	center[0] -= this->forwardSpeed;
	center[1] -= this->LeftSpeed;
	//center[2] += fabsf(speed) * forward_Vector[2];
	if (center[0] > 10.41) {
		eye[0] = center[0] + 5;
		eye[1] = center[1] + 0;
		eye[2] = center[2] + 4;
	}
	else {
		eye[0] = center[0] + 2;
		eye[1] = center[1] + 0;
		eye[2] = center[2] + 0;
	}

	//if (JudgeInside(center[0], center[1]) == true)
		//std::cout << center[1] << std::endl;
	

	GLUquadricObj *newSphere = gluNewQuadric();
	gluQuadricTexture(newSphere, true);
	gluSphere(newSphere, this->radius, 100, 100);
	//glutSolidTeapot(0.5);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	
}

