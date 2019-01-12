#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL\glut.h>
#include <math.h>
#include "Obj.h"

extern GLuint textures[3];;

using namespace std;

Obj::Obj(string filename)
{
	//obj±àºÅ
	obj_num = -1;

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
		if (content.size()>0 && (content[0] == "v" || content[0] == "f" || content[0] == "vn" || content[0] == "vt" || content[0] == "o"))
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
			if (content[0] == "vt") 
			{
				vector<GLfloat> vt;
				for (int i = 1; i < 4; i++)
				{
					GLfloat coordinate = atof(content[i].c_str());
					vt.push_back(coordinate);
				}
				vtSets.push_back(vt);
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
				vector<GLint> IndexVT;
				for (int i = 1; i < content.size(); i++)
				{
					string x = content[i];
					string v = "";
					string vn = "";
					string vt = "";
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
						else if (numSlash == 1 && ch != '/') {
							vt.append(1, ch);
						}
						else if (numSlash == 2 && ch != '/')
						{
							vn.append(1, ch);
						}
					}
					GLint ind = atoi(v.c_str());
					ind--;
					Index.push_back(ind);

					GLint invt;
					if (vt == "")
						invt = 0;
					else
						invt = atoi(vt.c_str());
					invt--;
					IndexVT.push_back(invt);

					GLint indn;
					if (vn == "")
						indn = 0;
					else
						indn = atoi(vn.c_str());
					indn--;
					IndexN.push_back(indn);
				}
				model[obj_num].fSets.push_back(Index);
				model[obj_num].fnSets.push_back(IndexN);
				model[obj_num].fvtSets.push_back(IndexVT);
			}
			else if(content[0] == "o")
			{
				obj_num++;
			}
		}
	}
	f.close();
}


void Obj::Draw(double size)
{
	//printf("%d\n", obj_num);

	GLfloat sun_ambient[] = { 0.0f,0.2f,0.2f,1.0f };
	GLfloat sun_diffuse[] = { 0.3f,0.2f,0.2f,1.0f };
	GLfloat sun_specular[] = { 0.2f,0.2f,0.0f,1.0f };
	GLfloat sun_emission[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat sun_shininess = 1.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sun_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sun_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sun_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_emission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sun_shininess);

	GLfloat VN[3], V[3], VT[3];

	glColor3f(0.2, 0.2, 0.2);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textures[2]);
	for (int num = 0; num <= obj_num; num++) {
		for (int i = 0; i < model[num].fSets.size(); i++)  //for every face needed to be drawed
		{
			if(num == 21) glBindTexture(GL_TEXTURE_2D, textures[2]);
			else if (num <= 55 && num >= 48) glBindTexture(GL_TEXTURE_2D, textures[1]);
			else glBindTexture(GL_TEXTURE_2D, textures[0]);
			glBegin(GL_POLYGON);
			for (int j = 0; j < model[num].fSets[i].size(); j++)  //for every vertex related with this face
			{
				GLint indexN = (model[num].fnSets[i])[j];
				if (indexN >= 0)
				{
					//glTexCoord2f(0.0, 0.0);
					VN[0] = (vnSets[indexN])[0];
					VN[1] = (vnSets[indexN])[1];
					VN[2] = (vnSets[indexN])[2];
					//glNormal3f(V[0], V[1], V[2]);  //set the normal
				}

				GLint indexVT = (model[num].fvtSets[i])[j];
				//printf("%d\n", indexVT);
				VT[0] = (vtSets[indexVT])[0];
				VT[1] = (vtSets[indexVT])[1];
				VT[2] = (vtSets[indexVT])[2];

				glTexCoord3f(VT[0], VT[1], VT[2]);

				GLint index = (model[num].fSets[i])[j];
				V[0] = (vSets[index])[0] * size;
				V[1] = (vSets[index])[1] * size;
				V[2] = (vSets[index])[2] * size;
				//printf("%d\n", index);

				//if (j == 0)
				//	glTexCoord2f(0, 0);
				//else if (j == 1)
				//	glTexCoord2f(0, 1);
				//else
				//{
				//	glTexCoord2f(1, 1);
				//}

				glVertex3f(V[0], V[1], V[2]);  //set one point for the polygon

			}
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
}
