#pragma once
#include "engine.h"
class ESP
{
public:
	ESP(Engine* pEngine);
	CEntity * GetPlayerByIndex(uint8_t i);
	CEntity * GetLocalPlayer();
	void Box2D(D3DXVECTOR3 Head, D3DXVECTOR3 Foot, DWORD dwColor);
	void DrawSkeleton(int *obj, D3DCOLOR dwColor);
	void InitPvP(int Status);
private:
	Engine *engine_;
};

