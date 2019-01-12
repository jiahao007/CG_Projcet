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
	vector<vector<GLfloat>> vertex;				//��������
	vector<vector<GLfloat>> vertex_texture;		//��������
	vector<vector<GLfloat>> vertex_normal;		//���㷨��
	vector<vector<int>> face_vertex;			//�涥������
	vector<vector<int>> face_texture;			//����������
	vector<vector<int>> face_normal;			//�淨������

public:
	ObjModel();
	~ObjModel();
	void readobj(string fileName);				//��ȡobjģ���ļ�
	void showobj();								//��ʾģ������
};