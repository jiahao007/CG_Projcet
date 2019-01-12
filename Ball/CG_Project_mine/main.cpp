#include <gl/glut.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include <vector>
#include"Ball.h"
#include "function.h"
#include "objModel.h"
#include "Obj.h"
#include"glassRectangle.h"
// This assignment may cost you some efferts, so I give you some important HINTS, hope that may help you.
// Enjoy the coding and thinking, do pay more attention to the library functions used in OPENGL, such as how they are used? what are the parameters used? and why?


float fTranslate;
float fRotate;
float fScale = 1.0f;    // set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;
//---------------
#define BITMAP_ID 0x4D42
#define WINDOW_HEIGHT 1280
#define WINDOW_WIDTH 720
const GLuint SCR_WIDTH = 1280;
const GLuint SCR_HEIGHT = 720;
float G_fDistance = 1.5f;
//物体的旋转角度 
float G_fAngle_horizon = 0.0;
float G_fAngle_vertical = 0.0f;

//设定读入的模型以及显示的方式
bool redraw = true;
ObjModel *obj1 = new ObjModel();
Obj *o = new Obj("C:/Users/Zihao Wang/Desktop/CG_Project_mine/obj/cgv5.obj");
string path = "C:/Users/Zihao Wang/Desktop/CG_Project_mine/obj/rubby.obj";
//light0参数
GLfloat Vp0[] = { 0.0,0.0,0.0,1.0 };	 //光源环境光位置
GLfloat Va0[] = { 0.8,0.8,0.8,1 };       //光源环境光强度数组  
GLfloat Vd0[] = { 0.6,0.6,0.6,1 };       //光源散射光强度数组  
GLfloat Vs0[] = { 0.5,0.5,0.5,1 };       //光源镜面反射光强度数组  
GLuint texture[6];


Ball ball;

bool isbrak = false;
glassRectangle glass1(-6.66, -0.02, -5.6, 3, 0.1, 3, 0, 0);
glassRectangle glass2(-12.66, -0.06, -5.6, 3, 0.1, 3, 0, 0);
glassRectangle glass3(-25.16, -0.46, -5.6, 3, 0.1, 3, 0, 0);
GLfloat color[4] = { 0.0,1.0,1.0,0.3 };
GLfloat time = 0;
GLfloat breaktime;

int flag1 = 0;
int flag2 = 0;
int flag3 = 0;

void myinit(void);
//void myReshape(GLsizei w, GLsizei h);
//void display(void);
void skybox();
void processSpecialKeys(int key, int x, int y);
//void processNormalKeys(unsigned char key, int x, int y);
unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
void texload(int i, const char *filename);

void myinit(void)
{
	glGenTextures(6, texture); // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组
	texload(0, "C:/Users/Zihao Wang/Desktop/CG_Project_mine/Textures/back.bmp");
	texload(1, "C:/Users/Zihao Wang/Desktop/CG_Project_mine/Textures/front.bmp");
	texload(2, "C:/Users/Zihao Wang/Desktop/CG_Project_mine/Textures/right.bmp");
	texload(3, "C:/Users/Zihao Wang/Desktop/CG_Project_mine/Textures/left.bmp");
	texload(4, "C:/Users/Zihao Wang/Desktop/CG_Project_mine/Textures/top.bmp");
	texload(5, "C:/Users/Zihao Wang/Desktop/CG_Project_mine/Textures/bottom.bmp");
	//your initialization code
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void texload(int i, const char *filename) {
	BITMAPINFOHEADER bitmapInfoHeader;// bitmap信息头
	unsigned char*bitmapData;// 纹理数据

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);

	glTexImage2D(GL_TEXTURE_2D,
		0, //mipmap层次(通常为，表示最上层) 
		GL_RGB,//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2 
		bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2 
		0, //边框(0=无边框, 1=有边框) 
		GL_RGB,//bitmap数据的格式
		GL_UNSIGNED_BYTE, //每个颜色数据的类型
		bitmapData);//bitmap数据指针  
					// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//S方向重复
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//T方向重复
}

unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;// bitmap文件头
	unsigned char*bitmapImage;// bitmap图像数据
	int imageIdx = 0;// 图像位置索引
	unsigned char tempRGB;// 交换变量

								 // 以“二进制+读”模式打开文件filename 
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) {
		printf("file not open\n");
		return NULL;
	}
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		printf("%s", filename);
		return NULL;
	}
	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件
	fclose(filePtr);
	return bitmapImage;
}

void skybox() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
	float skyHei = 100;                      //天空的高度
	float skyLen = 100;                   //天空的长度
	float skyWid = 100;
	//后
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1, 0);
	glVertex3f(skyLen, -skyHei, skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(skyLen, +skyHei, skyWid);
	glTexCoord2f(0, 1);
	glVertex3f(-skyLen, +skyHei, skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(-skyLen, -skyHei, skyWid);
	glEnd();
	//前
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1, 0);
	glVertex3f(-skyLen, -skyHei, -skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(-skyLen, skyHei, -skyWid);
	glTexCoord2f(0, 1);
	glVertex3f(skyLen, skyHei, -skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(skyLen, -skyHei, -skyWid);
	glEnd();
	//右面
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1, 0);
	glVertex3f(skyLen, -skyHei, -skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(skyLen, skyHei, -skyWid);
	glTexCoord2f(0, 1);
	glVertex3f(skyLen, skyHei, skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(skyLen, -skyHei, skyWid);
	glEnd();


	//左面
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1, 0);
	glVertex3f(-skyLen, -skyHei, skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(-skyLen, +skyHei, skyWid);
	glTexCoord2f(0, 1);
	glVertex3f(-skyLen, +skyHei, -skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(-skyLen, -skyHei, -skyWid);
	glEnd();

	//顶面
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0, 1);
	glVertex3f(-skyLen, skyHei, -skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(-skyLen, skyHei, skyWid);
	glTexCoord2f(1, 0);
	glVertex3f(skyLen, skyHei, skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(skyLen, skyHei, -skyWid);
	glEnd();

	//底面
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0, 1);
	glVertex3f(-skyLen, -skyHei, skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(-skyLen, -skyHei, -skyWid);
	glTexCoord2f(1, 0);
	glVertex3f(skyLen, -skyHei, -skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(skyLen, -skyHei, skyWid);
	glEnd();
	glDisable(GL_TEXTURE_2D);//关闭纹理

}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);                        // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                    // Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp) {
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
		gluPerspective(60, 0.7, 1, 80);
	}
	else
		glOrtho(-3, 3, -3, 3, -100, 100);

	glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)                                        // Prevent A Divide By Zero By
	{
		height = 1;                                        // Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': 
		ball.Forward();
		break;

	case 's':
		ball.Back();
		break;

	case 'a':
		ball.Left();
		break;

	case 'd':
		ball.Right();
		break;

	case '=':
		ball.Set_Material();
		break;

	case 'p':
		std::cout << "center[0]  " << ball.Get_Center(0) << std::endl;
		std::cout << "center[1]  " << ball.Get_Center(1) << std::endl;
		break;

	case ' ':
		ball.Stop();
		break;

//----------------------------
	case 'u':	//"u"
		G_fDistance -= 2.0f;
		break;
	case 'i':		//"i"
		G_fDistance += 2.0f;
		break;
	case 27:	//"esc"
		exit(0);
	case '1':
		path = "C:/Users/Zihao Wang/Desktop/CG_Project_mine/obj/rubby.obj";
		redraw = true; obj1->~ObjModel(); obj1 = new ObjModel(); break;
	case '2':
		path = "C:/Users/Zihao Wang/Desktop/CG_Project_mine/obj/bird.obj";
		redraw = true; obj1->~ObjModel(); obj1 = new ObjModel(); break;
	case '3':
		path = "C:/Users/Zihao Wang/Desktop/CG_Project_mine/obj/torus.obj";
		redraw = true; obj1->~ObjModel(); obj1 = new ObjModel(); break;
	case '4':
		path = "C:/Users/Zihao Wang/Desktop/CG_Project_mine/obj/wan.obj";
		redraw = true; obj1->~ObjModel(); obj1 = new ObjModel(); break;
	

	default:
		break;
	}
}

void redraw_fun()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                    // Reset The Current Modelview Matrix

	glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 400);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(ball.Get_Eye(0), ball.Get_Eye(1), ball.Get_Eye(2),
		ball.Get_Center(0), ball.Get_Center(1), ball.Get_Center(2),
		0, 0, 1);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_POSITION, Vp0);		//设置光源的位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, Va0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Vd0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Vs0);


	//glLightModeli(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHTING);



	//天空盒
	//glPushMatrix();
	skybox();
	//glPopMatrix();


	o->Draw(0.01);


	ball.Roll();

	//glPushMatrix();
	//if (!(ball.Get_Center(0)>=-6.66&&ball.Get_Center(0)<=-6.64)&&flag1==0)
	//	glass1.Draw(color, 200, 200);
	//else {
	//	printf("%d\n",flag1);
	//	flag1 = 1;
	//	glass1.Break(0.1, 0.1, breaktime, time);
	//	//time = time + 0.01;
	//}
	//glPopMatrix();

	glPushMatrix();
	if (!(ball.Get_Center(0) >= -12.66&&ball.Get_Center(0) <= -12.64) && flag2 == 0)
		glass2.Draw(color, 200, 200);
	else {
		//printf("2\n");
		flag2 = 1;
		glass2.Break(0.1, 0.1, breaktime, time);
		//time = time + 0.01;
	}
	glPopMatrix();

	glPushMatrix();
	if (!(ball.Get_Center(0) >= -25.20&&ball.Get_Center(0) <= -25.10) && flag3 == 0)
		glass3.Draw(color, 200, 200);
	else {
		flag3 = 1;
		glass3.Break(0.1, 0.1, breaktime, time);
		//time = time + 0.01;
	}
	glPopMatrix();

	//getFPS();

	glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		G_fAngle_horizon -= 10.0f;
		break;
	case GLUT_KEY_RIGHT:
		G_fAngle_horizon += 10.0f;
		break;
	case GLUT_KEY_UP:
		G_fAngle_vertical -= 10.0f;
		break;
	case GLUT_KEY_DOWN:
		G_fAngle_vertical += 10.0f;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");
	
	myinit();

	glutDisplayFunc(redraw_fun);
	glutReshapeFunc(reshape);
	//glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	Init();


	glutMainLoop();
	return 0;
}


