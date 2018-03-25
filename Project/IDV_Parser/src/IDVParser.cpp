#include <IDVParser.h>
#include <stdio.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

void IDVParser::PrintFromLibrary() {
	printf("Hello World from Static Library\n");
}

void IDVParser::ReadFile(string filename) {
	string currentline;
	std::ifstream myfile(filename);
	int n_temp;
	if (myfile.is_open())
	{
		//while (!getline(myfile, currentline).eof)
		while (getline(myfile, currentline))
		{
			int Pos = currentline.find("xof 0303txt 0032"); //check if file is compatible
			int Pos2 = 0;
			if (Pos != -1) {
				cout << currentline << endl;
			}
			// parsing vars
			float x = 0, y = 0, z = 0, u = 0, v = 0,  nVertexcount;
			unsigned int componentgetter = 0;
			char separator;

			//find meshes
			
			Pos = currentline.find("Mesh ");
			if (Pos != -1) {
				Pos = currentline.find("template");
				if (Pos == -1) {

					Pos2 = currentline.find("Mesh ");
					if (Pos != -1) {
						Pos = currentline.find("template");
						if (Pos == -1) {
						
						}
					}
					//check substring

					MESH_p currMesh; //make new mesh
					++n_meshes; // inc mesh counter
					//v_Meshes.push_back(currMesh); //put new mesh in mesh vector

					cout << "Vertexes start" << endl;
					myfile >> nVertexcount >> separator;
					cout << nVertexcount << endl;
					currMesh.n_Vertexes = nVertexcount;

				
					//vector<CVertexMesh_p> Verts_reader(nVertexcount);
					for (int i = 0; i < nVertexcount; ++i) {
						myfile >> x >> separator >> y >> separator >> z >> separator >> separator;
						CVertexMesh_p tmp;
						tmp.x = x;
						tmp.y = y;
						tmp.z = z;
						tmp.w = 1;
						currMesh.VB_mesh.push_back(tmp);
						/*currMesh.VB_mesh[i].x = x;
						currMesh.VB_mesh[i].y = y;
						currMesh.VB_mesh[i].z = z;
						currMesh.VB_mesh[i].w = 1;*/
						//Verts.push_back(V);
						/*Xvertex.push_back(x);
						Yvertex.push_back(y);
						Zvertex.push_back(z);*/
						//cout << Verts[i].x << ", " << Verts[i].y << ", " << Verts[i].z << endl;
						//std::cout << "Vertex: " << i + 1 << " || x: " << x << ", y: " << y << ", z: " << z << std::endl;
					}
					cout << "Vertexes end" << endl;
					myfile >> currMesh.n_Indexes >> separator;
					cout << "indexes start" << endl;
					cout << currMesh.n_Indexes << endl;
					for (int i = 0; i < currMesh.n_Indexes; i++) {
						myfile >> n_temp >> separator >> x >> separator >> y >> separator >> z >> separator >> separator;
						/*indices_reader[i] = ix;
						indices_reader[i+1] = iy;
						indices_reader[i+2] = iz;*/
						currMesh.IB_mesh.push_back(x);
						currMesh.IB_mesh.push_back(y);
						currMesh.IB_mesh.push_back(z);
						//cout << Xindex[i] << ", " << Yindex[i] << ", " << Zindex[i] << ", " << endl;
						//cout << indices_reader[i] << endl;
					}
					cout << "indexes end" << endl;
					Pos = currentline.find("MeshNormals normals");
					while (Pos == -1) {
						getline(myfile, currentline);
						Pos = currentline.find("MeshNormals normals");
					}
					if (Pos != -1) {
						cout << "Normals start" << endl;
						myfile >> n_temp >> separator;
						for (int i = 0; i < nVertexcount; i++) {
							myfile >> x >> separator >> y >> separator >> z >> separator >> separator;
							currMesh.VB_mesh[i].nx = x;
							currMesh.VB_mesh[i].ny = y;
							currMesh.VB_mesh[i].nz = z;
							currMesh.VB_mesh[i].nw = 1;
							//NX.push_back(nx);
							//NY.push_back(ny);
							//NZ.push_back(nz);
							//cout << Verts[i].nx << ", " << Verts[i].ny << ", " << Verts[i].nz << endl;
						}
						cout << "Normals end" << endl;
					}
					myfile >> currMesh.n_Indexes >> separator;
					//cout << nIndexcount << endl;
					cout << "indexes 2 start" << endl;
					for (int i = 0; i < currMesh.n_Indexes; i++) {
						myfile >> n_temp >> separator >> x >> separator >> y >> separator >> z >> separator >> separator;
						//Xindex.push_back(ix);
						//Yindex.push_back(iy);
						//Zindex.push_back(iz);
						//cout << ix << ", " << iy << ", " << iz << ", " << endl;
					}
					cout << "indexes 2 end" << endl;
					getline(myfile, currentline);
					getline(myfile, currentline);
					getline(myfile, currentline);
					getline(myfile, currentline);
					Pos = currentline.find("MeshTextureCoords tc0 {");
					while (Pos == -1) {
						getline(myfile, currentline);
						Pos = currentline.find("MeshTextureCoords tc0 {");
					}
					if (Pos != -1) {
						cout << "Textures start" << endl;
						myfile >> n_temp >> separator;
						for (int i = 0; i < nVertexcount; i++) {
							myfile >> u >> separator >> v >> separator >> separator;
							currMesh.VB_mesh[i].u = u;
							currMesh.VB_mesh[i].v = v;
							//Texture_U.push_back(tu);
							//Texture_V.push_back(tv);
							//cout << Verts[i].s << ", " << Verts[i].t << endl;
						}
						cout << "Textures end" << endl;
					}

					//for (int i = 0; i <currMesh.n_Indexes; i++) {
					//	currMesh.IB_mesh.push_back(index0[i]);
					//	//j++;
					//	currMesh.IB_mesh.push_back(index1[i]);
					//	//k++;
					//	currMesh.IB_mesh.push_back(index2[i]);
					//	//l++;
					//}

					Pos = currentline.find("MeshMaterialList mtls {");
					while (Pos == -1) {
						getline(myfile, currentline);
						Pos = currentline.find("MeshMaterialList mtls {");
					}
					if (Pos != -1) {
						//cout << "Materials start" << endl;
						//myfile >> v_Meshes[0].n_mats >> separator;
						myfile >> currMesh.n_mats >> separator; //get number of materials
						cout << "Materials start" << endl;
						for (int k = 0; k < currMesh.n_mats; ++k) {
							MATERIAL_p nu_mat;
							currMesh.Materials.push_back(nu_mat);
						}
						myfile >> n_temp >> separator; //get general indexes
						for (int i = 0; i < currMesh.n_Indexes; ++i) {
							myfile >> componentgetter >> separator;
							//currMesh.Materials[n_meshes].SubSet_IB.push_back(componentgetter);
							currMesh.Materials[componentgetter].SubSet_IB.push_back(currMesh.IB_mesh[i]);
							++i;
							currMesh.Materials[componentgetter].SubSet_IB.push_back(currMesh.IB_mesh[i]);
							++i;
							currMesh.Materials[componentgetter].SubSet_IB.push_back(currMesh.IB_mesh[i]);
							//material_indices.push_back(componentgetter);
						}
						cout << "Materials end" << endl;
						/*while (n_matCounter < Materials) {
							Pos = currentline.find("diffuseMap");
							if (Pos != -1) {
								getline(myfile, currentline);

							}
						}*/
					}
					Pos = currentline.find("Material Dflt_Material {");
					while (Pos == -1) {
						getline(myfile, currentline);
						Pos = currentline.find("Material Dflt_Material {");
					}
					if (Pos != -1) {
						int Pos2 = -1;
						for (int i = 0; i < currMesh.n_mats; ++i) {
							Pos = currentline.find("diffuseMap");
							Pos2 = currentline.find("diffuseColor");
							while (Pos2 == -1) {
								getline(myfile, currentline);
								Pos = currentline.find("diffuseColor");
							}
							if (Pos2 != -1) {
								getline(myfile, currentline);
								getline(myfile, currentline);
								myfile >> currMesh.Materials[i].R >> separator;
								myfile >> currMesh.Materials[i].G >> separator;
								myfile >> currMesh.Materials[i].B >> separator;
								myfile >> currMesh.Materials[i].A >> separator;
							}
							while (Pos == -1) {
								getline(myfile, currentline);
								Pos = currentline.find("diffuseMap");
							}
							if (Pos != -1) {
								getline(myfile, currentline);
								myfile >> separator >> currMesh.Materials[i].DifusemapPath;
							}
						}
					}
					v_Meshes.push_back(currMesh); //put new mesh in mesh vector
					//cout << "Materials end" << endl;
					//CVertex gets filled with data
					//currMesh.VB_mesh = Verts_reader;
					//int j = 0;
					//int k = 0;
					//int l = 0;
				}
			}

		}
		myfile.close();
		cout << "file at end sending data to draw" << endl;
	}
	else {
		std::cout << "file not found or is unreadable" << std::endl;
	}

}

void IDVParser::ParserInner_w_events(std::string filename, SDL_Event evento) {
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

