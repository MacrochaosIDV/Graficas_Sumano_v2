
#ifndef IDV_PARSER
#define IDV_PARSER

#include <SDL\SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;
using std::string;
//using namespace std::vector;

#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>

struct MATERIAL_p {
	std::vector<unsigned int> SubSet_IB; //subset index buffer
	unsigned int IB;
	ComPtr<ID3D11Buffer>		_IB;
	string DifusemapPath;
	float R;
	float G;
	float B;
	float A;
};
struct CVertexMesh_p {

	float x, y, z;
	float w = 1;
	float nx, ny, nz, nw;
	float u, v;
};
struct MESH_p {
	std::vector<CVertexMesh_p> VB_mesh;
	std::vector<unsigned int> IB_mesh; //general index buffer
	std::vector<MATERIAL_p> Materials; //to fill subsets
	//for(int i=0; i< IB_Meh.size();++i){
	//
	//
	unsigned int n_mats = 0;
	unsigned int n_Indexes = 0;
	unsigned int n_Vertexes = 0;
	unsigned int VB;
	unsigned int IB;
	ComPtr<ID3D11Buffer>		_VB;
	//
	//
	//
};
class IDVParser {
public:
	
	unsigned int n_meshes=-1;
	std::vector<MESH_p> v_Meshes;
	//std::vector<CVertexMesh_p> Verts_reader;

	//std::vector<CVertexMesh_p> VB_model;
	//std::vector<unsigned int> IB_model;
	//unsigned int	Vertexes;
	//unsigned int	Indexes;
	//unsigned int	Materials;

	/*std::vector<unsigned int> index0;
	std::vector<unsigned int> index1;
	std::vector<unsigned int> index2;*/

	IDVParser() {}
	void PrintFromLibrary();
	void ReadFile(std::string filename);
	void ParserInner_w_events(std::string filename, SDL_Event evento);
};


#endif