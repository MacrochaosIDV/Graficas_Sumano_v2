#include <IDVScene/IDVSceneProp.h>

void	SceneProps::AddLight(D3DXVECTOR3 Pos, D3DXVECTOR3 Color, bool enabled){
	Light l;
	l.Position=Pos;
	l.Color=Color;
	l.Enabled=(int)enabled;
	Lights.push_back(l);
}

void	SceneProps::RemoveLight(unsigned int index){
	if(index < 0 || index >= Lights.size())
		return;

	Lights.erase(Lights.begin() + index);
}

void	SceneProps::SetLightPos(unsigned int index, D3DXVECTOR3 pos){
	if (index < 0 || index >= Lights.size())
		return;

	Lights[index].Position = pos;
}