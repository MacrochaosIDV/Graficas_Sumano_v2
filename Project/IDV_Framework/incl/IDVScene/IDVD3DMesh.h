#pragma once
#ifndef IDV_MESH_D3D_H
#define IDV_MESH_D3D_H

#include <d3dx9math.h>

#include <vector>
#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>

#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>
#include <IDV_Math.h>
#include <IDVParser.h>

class D3DXMesh: public PrimitiveBase {
public:
	struct CBuffer {
		XMATRIX44 WVP;
		XMATRIX44 World;
		XMATRIX44 WorldView;
	};
	IDVParser parser;
	D3DXMesh(std::string path_n_Name) {}
	void Create() {}
	void Create(char *) {}
	void Create(std::string path_n_Name);
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;
	ComPtr<ID3D11SamplerState>  pSampler;

	CBuffer			CnstBuffer;
	//unsigned int	VB;
	//unsigned int  IB;

	XMATRIX44		transform;
};
#endif

