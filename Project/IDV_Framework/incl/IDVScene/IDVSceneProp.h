#ifndef IDV_SCENEPROPS_H
#define IDV_SCENEPROPS_H

#include <d3dx9math.h>

#include <vector>

struct Light{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Color;
	int		 Type;
	int		 Enabled;
};

struct SceneProps{
	SceneProps() : ActiveCamera(0) , ActiveLights(1), ActiveLightCamera(0), ActiveGaussKernel(0), Exposure(0.3f) , BloomFactor(1.1f) {}

	void	AddLight(D3DXVECTOR3 Pos, D3DXVECTOR3 Color,bool enabled);
	void	RemoveLight(unsigned int index);
	void	SetLightPos(unsigned int index, D3DXVECTOR3);

	std::vector<Light>	   Lights;

	D3DXVECTOR3			AmbientColor;

	int ActiveCamera;
	int	ActiveLights;
	int ActiveLightCamera;
	int ActiveGaussKernel;
	
	// HDR
	float	Exposure;
	float	BloomFactor;
};

#endif
