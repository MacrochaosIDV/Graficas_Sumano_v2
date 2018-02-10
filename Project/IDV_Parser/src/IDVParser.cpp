#include <IDVParser.h>
#include <stdio.h>

std::vector<CVertexMesh> Verts_reader;

void PrintFromLibrary() {
	printf("Hello World from Static Library\n");
}

void ReadFile(std::string filename) {
	std::string currentline;
	std::ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, currentline))
		{
			int Pos = currentline.find("xof 0303txt 0032");
			if (Pos != -1) {
				std::cout << currentline << std::endl;
			}
			float x = 0, y = 0, z = 0, nVertexcount;
			char separator;

			Pos = currentline.find("Mesh ");
			if (Pos != -1) {
				Pos = currentline.find("template");
				if (Pos == -1) {
					std::cout << "Vertexes start" << std::endl;
					myfile >> nVertexcount >> separator;
					std::cout << nVertexcount << std::endl;
					std::vector<CVertexMesh> Verts_reader(nVertexcount);
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
						std::cout << "Vertex: " << i + 1 << " || x: " << x << ", y: " << y << ", z: " << z << std::endl;
					}
					myfile.close();
				}

			}
			else {
				std::cout << "file nor found or is unreadable" << std::endl;
			}
		}
	}
}

void ParserInner_w_events(std::string filename, SDL_Event evento) {
	bool getNextLine = false;
	bool getAllFile = false;
	std::string currentline;
	std::ifstream myfile(filename);
	while (myfile.is_open())
	{
		if (true) {

		}
		else {
			std::cout << "file nor found or is unreadable" << std::endl;
		}
	}
}

