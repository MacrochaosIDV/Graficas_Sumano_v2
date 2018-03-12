#pragma once
#ifndef IDV_MESH_GL_H
#define IDV_MESH_GL_H

#include <d3dx9math.h>
#include <IDV_Math.h>
#include <GL/glew.h>
#include <vector>
#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>
#include <IDVParser.h>
//struct MATERIAL {
//	std::vector<unsigned short> Index_mat;
//};
//struct CVertexMesh {
//
//	float x, y, z;
//	float w = 1;
//	float nx, ny, nz, nw;
//	float u, v;
//};
//struct MESH {
//	std::vector<CVertexMesh> VB_mesh;
//	std::vector<unsigned int> IB_mesh;
//	std::vector<MATERIAL> Materials;
//};
class GLMesh: public PrimitiveBase {
public:
	
	IDVParser parser;
	GLMesh(std::string path_n_Name) {}
	void Create();
	void Create(char *) {}
	void Create(std::string path_n_Name);
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	//std::vector<CVertexMesh> VB_model;
	//std::vector<unsigned int> IB_model;
	//unsigned int	Vertexes;
	//unsigned int	Indexes;
	XMATRIX44		transform;
};
#endif

