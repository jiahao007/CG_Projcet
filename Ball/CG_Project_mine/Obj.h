#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL\glut.h>
#include <math.h>
using namespace std;

class Obj {
public:
	Obj(string filename);
	void Draw();
	void Draw(double size);
private:
	vector<vector<GLfloat>> vSets;  //save coordinates for all vertexs
	vector<vector<GLfloat>> vnSets;  //save all normals
	vector<vector<GLint>> fSets;   //save all faces' related vertexs' indexes
	vector<vector<GLint>> fnSets;   //save all faces' related normals' indexes
};

