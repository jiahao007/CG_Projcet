#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const float AngleToRadion = 3.1415926 / 189.0;

class ObjModel {
private:
	vector<vector<GLfloat>> vertex;				//顶点坐标
	vector<vector<GLfloat>> vertex_texture;		//顶点纹理
	vector<vector<GLfloat>> vertex_normal;		//顶点法向
	vector<vector<int>> face_vertex;			//面顶点索引
	vector<vector<int>> face_texture;			//面纹理索引
	vector<vector<int>> face_normal;			//面法向索引

public:
	ObjModel();
	~ObjModel();
	void readobj(string fileName);				//读取obj模型文件
	void showobj();								//显示模型数据
};