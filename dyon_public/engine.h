#pragma once
#include "stdafx.h"
#include "log.h"
#include "sdk.h"
#include "menu.h"

class Engine
{
public:
	Engine(Log* log);
	_IntersectSegment IntersectSegment;
	bool Init();
	DWORD getLocalPlayerFunc();
	DWORD getIntersectSegment();
	void HookFlipScreen(uint32_t routine, uint32_t * original);
	IDirect3DDevice9 *GetDevice();
	bool WorldToScreen(D3DXVECTOR3 * vWorldLocation, D3DXVECTOR3 * vScreenCoord);
	void Run();
	bool __cdecl Engine::IsVisible(D3DXVECTOR3 MePos, D3DXVECTOR3 TargetPos);
	bool ValidPointer(void* Pointer)
	{
		return !IsBadReadPtr(Pointer, 4) && Pointer;
	}
	int32_t esp_status_;
private:
	Menu* menu_;
	bool initialized_ = false;
	HMODULE	hCShell, hClientFxD;
	Log* file_log_;
	uint32_t cshell_base_;
	uint32_t deviceGame_;
	uint32_t flipscreen_;
	uint32_t call_to_flipscreen_;
	uint32_t address_of_cGame;
	uint32_t getlocalplayer_;
	uint32_t address_of_intersect_;
	int32_t wallhack_status_;
	int32_t seeghost_status_;
	int32_t phantom_status_;
};

