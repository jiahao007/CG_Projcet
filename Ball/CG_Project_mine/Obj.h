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
	//0-4为圆柱
	//5为轨道
	//6-11
	//12-13右大块
	//14-15左大块
	//16左次大块
	//17右次大块
	//18大门挖空圆柱
	//19大门圆环突出
	//20大门长方体
	//21大门上方按钮
	//22-25畸形门1
	//26-29畸形门2
	//30畸形门12右墙
	//31畸形门12左墙
	//32-37方块
	//38畸形门34右墙
	//39畸形门34左墙
	//40-43畸形门4
	//44-47畸形门3
	//48-55擎天柱
};

