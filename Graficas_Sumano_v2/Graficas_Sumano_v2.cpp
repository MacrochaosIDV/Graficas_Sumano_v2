// Graficas_Sumano_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



struct CVertexMesh {

	float x, y, z;
	float w = 1;
	float nx, ny, nz, nw;
	float s, t;
};

vector<CVertexMesh> Verts_reader;

void ReadFile(string filename) {
	string currentline;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, currentline))
		{
			int Pos = currentline.find("xof 0303txt 0032");
			if (Pos != -1) {
				cout << currentline << endl;
			}
			float x = 0, y = 0, z = 0, nVertexcount;
			char separator;

			Pos = currentline.find("Mesh ");
			if (Pos != -1) {
				Pos = currentline.find("template");
				if (Pos == -1) {
					cout << "Vertexes start" << endl;
					myfile >> nVertexcount >> separator;
					cout << nVertexcount << endl;
					vector<CVertexMesh> Verts_reader(nVertexcount);
					for (int i = 0; i < nVertexcount; ++i) {
						myfile >> x >> separator >> y >> separator >> z >> separator >> separator;
						Verts_reader[i].x = x;
						Verts_reader[i].y = y;
						Verts_reader[i].z = z;
						Verts_reader[i].w = 1;
						//Verts.push_back(V);
						/*Xvertex.push_back(x);
						Yvertex.push_back(y);
						Zvertex.push_back(z);*/
						//cout << Verts[i].x << ", " << Verts[i].y << ", " << Verts[i].z << endl;
						cout << "Vertex: " << i + 1 << " || x: " << x << ", y: " << y << ", z: " << z << endl;
					}
					myfile.close();
				}

			}
			else {
				cout << "file nor found or is unreadable" << endl;
			}
		}
	}
}

int main()
{
	ReadFile("CerdoNuevo.X");
    return 0;
}

