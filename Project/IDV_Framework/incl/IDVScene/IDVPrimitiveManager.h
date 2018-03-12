#ifndef IDV_PRIMITIVEMANAGER_H
#define IDV_PRIMITIVEMANAGER_H

#include <d3dx9math.h>

#include <vector>
#include <IDVScene/IDVGLMesh.h>
#include <IDVScene/IDVD3DMesh.h>
#include <IDVVideo/IDVBaseDriver.h>
#include <IDVScene/IDVPrimitive.h>
#include <IDVScene/IDVSceneProp.h>

class PrimitiveManager {
public:
	PrimitiveManager(IDVAPI Selected) { SelectedApi = Selected;  }
	void SetVP(XMATRIX44 *vp) {
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
	XMATRIX44 *pVP;
};

#endif
