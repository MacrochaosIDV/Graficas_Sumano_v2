#ifndef IDV_PRIMITIVEMANAGER_H
#define IDV_PRIMITIVEMANAGER_H

#include <d3dx9math.h>

#include <vector>

#include <IDVVideo/IDVBaseDriver.h>
#include <IDVScene/IDVPrimitive.h>
#include <IDVScene/IDVSceneProp.h>

class PrimitiveManager {
public:
	PrimitiveManager(IDVAPI Selected) { SelectedApi = Selected;  }
	void SetVP(D3DXMATRIX *vp) {
		pVP = vp;
	}
	int  CreateQuad();
	int  CreateMesh(std::string path);
	void SetSceneProps(SceneProps *p);

	void DrawPrimitives();
	void DestroyPrimitives();
	PrimitiveBase*	GetPrimitive(unsigned int);

	std::vector<PrimitiveBase*> primitives;

	IDVAPI		SelectedApi;
	D3DXMATRIX *pVP;
};

#endif
