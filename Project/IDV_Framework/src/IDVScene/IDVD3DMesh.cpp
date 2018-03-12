#include <IDVVideo/IDVD3DXShader.h>
#include <IDVScene/IDVD3DMesh.h>
#include <IDVUtils/IDVUtils.h>

extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;

void D3DXMesh::Create(std::string path_n_Name) {
	SigBase = IDVSig::HAS_TEXCOORDS0;

	char *vsSourceP = file2string("Shaders/VS_Quad.hlsl");
	char *fsSourceP = file2string("Shaders/FS_Quad.hlsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	int shaderID = g_pBaseDriver->CreateShader(vstr, fstr, SigBase);

	//vertex read
	parser.ReadFile(path_n_Name);

	IDVD3DXShader* s = dynamic_cast<IDVD3DXShader*>(g_pBaseDriver->GetShaderIdx(shaderID));

	D3D11_BUFFER_DESC bdesc = { 0 }; //
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.ByteWidth = sizeof(CBuffer);
	bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = D3D11Device->CreateBuffer(&bdesc, 0, pd3dConstantBuffer.GetAddressOf());
	if (hr != S_OK) {
		printf("Error Creating Constant Buffer\n");
		return;
	}

	bdesc = { 0 };
	//bdesc.ByteWidth = sizeof(CVertexMesh) * 4;
	bdesc.ByteWidth = sizeof(CVertexMesh_p) * 4;
	bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//WHERE DO I PUT THE FORFOR!?!?!
	for (int i = 0; i < parser.n_meshes; ++i) {
		D3D11_SUBRESOURCE_DATA subData = { &parser.v_Meshes[i].VB_mesh[0] , 0, 0 }; //Vertexes
																					//D3D11_SUBRESOURCE_DATA subData = { &Verts[0], 0, 0 };
		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &VB);
		if (hr != S_OK) {
			printf("Error Creating Vertex Buffer\n");
			return;
		}
		for (int j = 0; j < parser.v_Meshes[i].n_mats; ++j) {
			
			bdesc = { 0 };
			bdesc.ByteWidth = parser.v_Meshes[i].n_Indexes * sizeof(USHORT);
			bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			subData = { &parser.v_Meshes[i].Materials[j].SubSet_IB[0], 0, 0 };//Indexes
			hr = D3D11Device->CreateBuffer(&bdesc, &subData, &IB);
			if (hr != S_OK) {
				printf("Error Creating Index Buffer\n");
				return;
			}
			D3D11_SAMPLER_DESC sdesc;
			sdesc.Filter = D3D11_FILTER_ANISOTROPIC;
			sdesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
			sdesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
			sdesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
			sdesc.MinLOD = 0;
			sdesc.MaxLOD = D3D11_FLOAT32_MAX;
			sdesc.MipLODBias = 0.0f;
			sdesc.MaxAnisotropy = 1;
			sdesc.BorderColor[0] = sdesc.BorderColor[1] = sdesc.BorderColor[2] = sdesc.BorderColor[3] = 0;
			D3D11Device->CreateSamplerState(&sdesc, pSampler.GetAddressOf());
		}
	}
}

void D3DXMesh::Transform(float *t) {
	transform = t;
}

void D3DXMesh::Draw(float *t, float *vp) {

	if (t)
		transform = t;

	unsigned int sig = SigBase;
	sig |= gSig;
	IDVD3DXShader * s = dynamic_cast<IDVD3DXShader*>(g_pBaseDriver->GetShaderSig(sig));
	UINT offset = 0;
	UINT stride = sizeof(CVertexMesh_p);
	//UINT stride = sizeof(CVertexMesh);

	XMATRIX44 VP = vp;
	CnstBuffer.WVP = transform;
	CnstBuffer.World = transform;
	CnstBuffer.WorldView = transform;
	D3D11DeviceContext->VSSetShader(s->pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(s->pFS.Get(), 0, 0);
	D3D11DeviceContext->IASetInputLayout(s->Layout.Get());

	D3D11DeviceContext->UpdateSubresource(pd3dConstantBuffer.Get(), 0, 0, &CnstBuffer, 0, 0);
	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	for (int i = 0; i < parser.n_meshes; ++i) {
		D3D11DeviceContext->IASetIndexBuffer(IB.Get(), DXGI_FORMAT_R16_UINT, 0);
		D3D11DeviceContext->IASetVertexBuffers(0, 1, VB.GetAddressOf(), &stride, &offset);
		
		for (int j = 0; j < parser.v_Meshes[i].n_mats; ++j) {
			D3D11DeviceContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
			D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			D3D11DeviceContext->DrawIndexed(parser.v_Meshes[i].Materials[j].SubSet_IB[0], 0, 0);
			//D3D11DeviceContext->DrawIndexed(6, 0, 0);
		}
	}
}

void D3DXMesh::Destroy() {
}
