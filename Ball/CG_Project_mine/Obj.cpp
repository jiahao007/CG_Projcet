#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL\glut.h>
#include <math.h>
#include "Obj.h"

using namespace std;

Obj::Obj(string filename)
{
	string line;
	fstream f;
	f.open(filename, ios::in);
	if (!f.is_open()) {
		cout << "Error with open obj file." << endl;
	}
	cout << "Reading data...This may take about two minutes...Thank you for your patience" << endl;
	cout << "After the window appears, please wait another several seconds for drawing to finish " << endl;
	while (!f.eof())
	{
		getline(f, line);
		vector<string> content;
		string tailmark = " ";
		string s = "";
		line = line.append(tailmark);
		for (int i = 0; i < line.length(); i++)
		{
			char ch = line[i];
			if (ch != ' ')
			{
				s.append(1, ch);
			}
			else if (s.length()>0)
			{
				content.push_back(s);
				s = "";
			}
		}  //do the "split" work
		if (content.size()>0 && (content[0] == "v" || content[0] == "f" || content[0] == "vn"))
		{
			if (content[0] == "v") //this line is a coordinate for a vertex
			{
				vector<GLfloat> Point;
				for (int i = 1; i < 4; i++)
				{
					GLfloat coordinate = atof(content[i].c_str());
					Point.push_back(coordinate);
				}
				vSets.push_back(Point); //save this point into vsets
			}
			else if (content[0] == "vn")  //if this line is about normal
			{
				vector<GLfloat> PointN;
				for (int i = 1; i < 4; i++)
				{
					GLfloat coordinateN = atof(content[i].c_str());
					PointN.push_back(coordinateN);
				}
				vnSets.push_back(PointN);
			}
			else if (content[0] == "f")  //if this line is about a face, need to get both vertex and normal infomation
			{
				vector<GLint> Index;
				vector<GLint> IndexN;
				for (int i = 1; i < content.size(); i++)
				{
					string x = content[i];
					string v = "";
					string vn = "";
					int numSlash = 0;
					for (int j = 0; j < x.length(); j++)
					{
						char ch = x[j];
						if (numSlash == 0 && ch != '/')
						{
							v.append(1, ch);
						}
						else if (ch == '/')
						{
							numSlash++;
						}
						else if (numSlash == 2 && ch != '/')
						{
							vn.append(1, ch);
						}
					}
					GLint ind = atoi(v.c_str());
					ind--;
					Index.push_back(ind);
					GLint indn;
					if (vn == "")
						indn = 0;
					else
						indn = atoi(vn.c_str());
					indn--;
					IndexN.push_back(indn);
				}
				fSets.push_back(Index);
				fnSets.push_back(IndexN);
			}
		}
	}
	f.close();
}

void Obj::Draw()
{
	GLfloat VN[3], V[3];
	for (int i = 0; i < fSets.size(); i++)  //for every face needed to be drawed
	{
		glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 0.0);
		for (int j = 0; j < fSets[i].size(); j++)  //for every vertex related with this face
		{
			GLint indexN = (fnSets[i])[j];
			if (indexN >= 0)
			{
				VN[0] = (vnSets[indexN])[0];
				VN[1] = (vnSets[indexN])[1];
				VN[2] = (vnSets[indexN])[2];
				glNormal3f(VN[0], VN[1], VN[2]);  //set the normal
			}
			GLint index = (fSets[i])[j];
			V[0] = (vSets[index])[0];
			V[1] = (vSets[index])[1];
			V[2] = (vSets[index])[2];
			glVertex3f(V[0], V[1], V[2]);  //set one point for the polygon
		}
		glEnd();
	}
}

void Obj::Draw(double size)
{
	GLfloat VN[3], V[3];
	for (int i = 0; i < fSets.size(); i++)  //for every face needed to be drawed
	{
		glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 0.0);
		for (int j = 0; j < fSets[i].size(); j++)  //for every vertex related with this face
		{
			GLint indexN = (fnSets[i])[j];
			if (indexN >= 0)
			{
				VN[0] = (vnSets[indexN])[0] * size;
				VN[1] = (vnSets[indexN])[1] * size;
				VN[2] = (vnSets[indexN])[2] * size;
				glNormal3f(VN[0], VN[1], VN[2]);  //set the normal
			}
			GLint index = (fSets[i])[j];
			V[0] = (vSets[index])[0] * size;
			V[1] = (vSets[index])[1] * size;
			V[2] = (vSets[index])[2] * size;
			glVertex3f(V[0], V[1], V[2]);  //set one point for the polygon
		}
		glEnd();
	}
}
