#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL\glut.h>
#include <math.h>
using namespace std;

typedef struct _obj {
	vector<vector<GLint>> fSets;
	vector<vector<GLint>> fnSets;
	vector<vector<GLint>> fvtSets;
}obj;

class Obj {
public:
	Obj(string filename);
	void Draw();
	void Draw(double size);
private:
	GLint obj_num;
	vector<vector<GLfloat>> vSets;  //save coordinates for all vertexs
	vector<vector<GLfloat>> vnSets;  //save all normals
	vector<vector<GLfloat>> vtSets;
	vector<vector<GLint>> fSets;   //save all faces' related vertexs' indexes
	vector<vector<GLint>> fnSets;   //save all faces' related normals' indexes
	vector<vector<GLint>> fvtSets;
	obj model[56];
	//0-4ΪԲ��
	//5Ϊ���
	//6-11
	//12-13�Ҵ��
	//14-15����
	//16��δ��
	//17�Ҵδ��
	//18�����ڿ�Բ��
	//19����Բ��ͻ��
	//20���ų�����
	//21�����Ϸ���ť
	//22-25������1
	//26-29������2
	//30������12��ǽ
	//31������12��ǽ
	//32-37����
	//38������34��ǽ
	//39������34��ǽ
	//40-43������4
	//44-47������3
	//48-55������
};

