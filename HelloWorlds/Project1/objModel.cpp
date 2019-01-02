#include "objModel.h"

int typecheck(string line, char tag);
void setfaceinfo(string line, vector<int> &v, vector<int> &vs);
void setfaceinfo(string line, vector<int> &v, vector<int> &vt, vector<int> &vn);

ObjModel::ObjModel() {

}

/*
 *析构函数，清空obj模型中的所有数据
 */
ObjModel::~ObjModel()
{
	vertex.clear();
	vertex_texture.clear();
	vertex_normal.clear();
	face_vertex.clear();
	face_texture.clear();
	face_normal.clear();
}

/*
 * 从obj文件中读取相应数据
 * @para fileName: the name of the objmodel
 */
void ObjModel::readobj(string fileName)
{
	ifstream is;
	string line;
	int cnt = 0;
	is.open(fileName.c_str(), ios::in);
	if (!is.is_open())
	{
		cout << "打开文件失败" << endl;
		is.close();
		exit(0);
	}
	while (!is.eof())
	{
		getline(is, line);
		//cout << line << endl;
		vector<GLfloat> tmp(3);
		//过滤掉空行和注释
		if (line.size() == 0 || line[0] == '#' || line[0] == 'o' || line[0] == 'u')
			continue;
		//行数据为纹理坐标
		else if (line.substr(0, 2) == "vt")
		{
			std::istringstream s(line.substr(2));
			s >> tmp[0] >> tmp[1] >> tmp[2];
			vertex_texture.push_back(tmp);
		}
		//行数据为法向坐标
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream s(line.substr(2));
			s >> tmp[0] >> tmp[1] >> tmp[2];
			vertex_normal.push_back(tmp);
		}
		else if (line.substr(0, 1) == "v")
		{
			std::istringstream s(line.substr(1));
			s >> tmp[0] >> tmp[1] >> tmp[2];
			vertex.push_back(tmp);
		}
		else if (line.substr(0, 1) == "f")
		{
			
			vector<int> v(3);
			vector<int> vt(3);
			vector<int> vn(3);
			std::istringstream s(line.substr(1));
			//面索引信息格式为 V1 V2 V3
			if (typecheck(line, '/') == 0)
			{
				s >> v[0] >> v[1] >> v[2];
				face_vertex.push_back(v);
			}
			//面索引信息格式为V1/T1 V2/T2 V3/T3
			else if (typecheck(line, '/') == 3)
			{
				setfaceinfo(line, v, vt);
				face_vertex.push_back(v);
				face_texture.push_back(vt);
			}
			//面索引信息格式为V1/T1/N1 V2/T2/N2 V3/T3/N3
			else if (typecheck(line, '/') == 6)
			{	
				setfaceinfo(line, v, vt, vn);
				face_vertex.push_back(v);
				face_texture.push_back(vt);
				face_normal.push_back(vn);	
			}
			//面索引信息格式为V1//N1 V2//N2 V3//N3
			else if (typecheck(line, '//') == 3)
			{
				setfaceinfo(line, v, vn);
				face_vertex.push_back(v);
				face_normal.push_back(vn);
			}
		}
	}
}

void ObjModel::showobj()
{
	for (int i = 0; i < face_vertex.size(); i++) //每个需要绘制的面块
	{
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		for (int j = 0; j < face_vertex[i].size(); j++) //面块上的每个点
		{
			//glNormal3f(vertex_normal[face_normal[i][0] - 1][0], vertex_normal[face_normal[i][0] - 1][1], vertex_normal[face_normal[i][0] - 1][2]);
			//glNormal3f(vertex_normal[face_vertex[i][0] - 1][0], vertex_normal[face_vertex[i][0] - 1][1], vertex_normal[face_vertex[i][0] - 1][2]);
			glVertex3f(vertex[face_vertex[i][0] - 1][0], vertex[face_vertex[i][0] - 1][1], vertex[face_vertex[i][0] - 1][2]);

			//glNormal3f(vertex_normal[face_vertex[i][1] - 1][0], vertex_normal[face_vertex[i][1] - 1][1], vertex_normal[face_vertex[i][1] - 1][2]);
			glVertex3f(vertex[face_vertex[i][1] - 1][0], vertex[face_vertex[i][1] - 1][1], vertex[face_vertex[i][1] - 1][2]);

			//glNormal3f(vertex_normal[face_vertex[i][2] - 1][0], vertex_normal[face_vertex[i][2] - 1][1], vertex_normal[face_vertex[i][2] - 1][2]);
			glVertex3f(vertex[face_vertex[i][2] - 1][0], vertex[face_vertex[i][2] - 1][1], vertex[face_vertex[i][2] - 1][2]);
		}
		glEnd();
	}
}

/*
 *检查face信息的类型
 *@para line face行信息
 *@para tag 检查标签
 */
int typecheck(string line, char tag)
{
	int cnt = 0;
	for (int i = 0; i <= line.size(); i++)
	{
		if (line[i] == tag)
			cnt++;
	}
	return cnt;
	
}

/*
 *根据每行信息，解析出face的顶点，法向，纹理索引
 *@para line 行信息
 *@para &v 顶点集合
 *@para &vt 纹理集合
 *@para &vn 法向集合
 */
void setfaceinfo(string line, vector<int> &v, vector<int> &vt, vector<int> &vn)
{
	int tmp = 0;
	int index = 0;
	vector<int> num(9);
	for (int i = 0; i <= line.size() && index < 9; i++)
	{
		if (line[i] >= '0' && line[i] <= '9')
			tmp = tmp * 10 + line[i] - '0';
		else
		{
			if (tmp != 0)
			{
				num[index++] = tmp;
				tmp = 0;
			}
		}
	}
	v[0] = num[0]; vt[0] = num[1]; vn[0] = num[2];
	v[1] = num[3]; vt[1] = num[4]; vn[1] = num[5];
	v[2] = num[6]; vt[2] = num[7]; vn[2] = num[8];
}

/*重载函数setfaceinfo()
*@para line 行信息
*@para &v 顶点集合
*@para &vs 纹理集合或法向集合
*/
void setfaceinfo(string line, vector<int> &v, vector<int> &vs)
{
	int tmp = 0;
	int index = 0;
	vector<int> num(6);
	for (int i = 0; i <= line.size() && index < 6; i++)
	{
		if (line[i] >= '0' && line[i] <= '9')
			tmp = tmp * 10 + (line[i] - '0');
		else
		{
			if (tmp != 0)
			{
				num[index++] = tmp;
				tmp = 0;
			}
		}
	}
	v[0] = num[0]; vs[0] = num[1];
	v[1] = num[2]; vs[1] = num[3];
	v[2] = num[4]; vs[2] = num[5];
}

