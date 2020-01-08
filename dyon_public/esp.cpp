#include "stdafx.h"
#include "esp.h"
#include "d3d.h"

ESP::ESP(Engine* pEngine){
	this->engine_ = pEngine;
}

__forceinline CEntity* ESP::GetPlayerByIndex(uint8_t i){
	CEntity* player = nullptr;

	if (i > 0 && i <= 16)
	{
		player = (CEntity *)((DWORD)CF_ENTRY::Instance()->pClientShellStub + (OFFSET_PLAYERSIZE * i) + OFFSET_PLAYERSTART);
	}
	return player;
}
__forceinline CEntity* ESP::GetLocalPlayer(){
	using GetLocalPlayer_t = uint8_t(__thiscall *)(DWORD);

	static DWORD dwGetLocalPlayerFnc = this->engine_->getLocalPlayerFunc();

	return GetPlayerByIndex(reinterpret_cast<GetLocalPlayer_t>(dwGetLocalPlayerFnc)((DWORD)CF_ENTRY::Instance()->pClientShellStub));
}
void ESP::Box2D(D3DXVECTOR3 Head, D3DXVECTOR3 Foot, DWORD dwColor){
	D3DXVECTOR3 Box = Head - Foot;

	if (Box.y < 0)
		Box.y *= -1;

	int BoxWidth = (int)Box.y / 2;
	int DrawX = (int)Head.x - (BoxWidth / 2);
	int DrawY = (int)Head.y;

	DrawBorder(DrawX + 1, DrawY, BoxWidth, (int)Box.y, 1, COLOR_BLACK, this->engine_->GetDevice());
	DrawBorder(DrawX, DrawY, BoxWidth, (int)Box.y, 1, dwColor, this->engine_->GetDevice());
}
void ESP::DrawSkeleton(int* obj, D3DCOLOR dwColor)//https://www.mpgh.net/forum/showthread.php?t=1435038
{
	if (obj)
{
		HMODELNODE hCurNode = INVALID_MODEL_NODE;
		while (CF_ENTRY::Instance()->pLTCSBase->GetLTModel()->GetNextNode(obj, hCurNode, hCurNode) == 0)
		{
			unsigned int parent = 0;
			CF_ENTRY::Instance()->pLTCSBase->GetLTModel()->GetParent(obj, hCurNode, parent);

			unsigned int ChildNodeCount = 0;
			CF_ENTRY::Instance()->pLTCSBase->GetLTModel()->GetNumChildren(obj, hCurNode, ChildNodeCount);

			for (uint32_t i = 0; i < ChildNodeCount; ++i)
			{
				HMODELNODE hChildNode = INVALID_MODEL_NODE;
				CF_ENTRY::Instance()->pLTCSBase->GetLTModel()->GetChild(obj, hCurNode, i, hChildNode);

				unsigned int parents = 0;
				CF_ENTRY::Instance()->pLTCSBase->GetLTModel()->GetParent(obj, hChildNode, parents);

				D3DXVECTOR3 StartPos, EndPos;

				LTransform Trans1;
				CF_ENTRY::Instance()->pLTCSBase->GetLTModel()->GetNodeTransform(obj, hChildNode, Trans1, true);
				StartPos = Trans1.m_vPos;
				StartPos.y += 5;

				LTransform Trans2;
				CF_ENTRY::Instance()->pLTCSBase->GetLTModel()->GetNodeTransform(obj, parents, Trans2, true);
				EndPos = Trans2.m_vPos;
				EndPos.y += 5;


				if (this->engine_->WorldToScreen(&EndPos, &EndPos) && this->engine_->WorldToScreen(&StartPos, &StartPos))
				{
					DrawLine(StartPos.x, StartPos.y, EndPos.x, EndPos.y, dwColor, this->engine_->GetDevice());
				}
			}
		}
	}
}
void ESP::InitPvP(int Status) {
	if (CF_ENTRY::Instance()->pClientShellStub->getLocalClient() == 0)
		return;

	auto pLocal = GetLocalPlayer();

	if (!pLocal)
		return;
	if (!pLocal->Object)
		return;
	
	for (int i = 0; i <= 16; i++)
	{
		auto pEnemy = GetPlayerByIndex(i); 
		
		if (pEnemy == 0)
			continue;
		

		if (pEnemy->iHealth <= 0)
			continue;

		if (pEnemy->ClientID == pLocal->ClientID)
			continue;
		DWORD ESP_COLOR;

		if (pLocal->Team != pEnemy->Team) {
			ESP_COLOR = COLOR_RED;
		}else if(pLocal->Team == pEnemy->Team) {
			ESP_COLOR = COLOR_BLUE;
		}

		D3DXVECTOR3 vEnemyPos = { 0.0F, 0.0F, 0.0F };
		D3DXVECTOR3 vMePos = { 0.0F, 0.0F, 0.0F };
		if (CF_ENTRY::Instance()->pLTCSBase->GetObjectPos(pEnemy->Object, &vEnemyPos) != 0) // get bone head it's better
			return;

		if (CF_ENTRY::Instance()->pLTCSBase->GetObjectPos(pLocal->Object, &vMePos) != 0)	// get bone head it's better
			return;

		if (this->engine_->IsVisible(vMePos, vEnemyPos)) {
			ESP_COLOR = COLOR_GREEN;
		}
		D3DXVECTOR3 vHead = { 0.0F, 0.0F, 0.0F };
		D3DXVECTOR3 vFoot = { 0.0F, 0.0F, 0.0F };
		if (CF_ENTRY::Instance()->pLTCSBase->GetObjectBoxMax(pEnemy->Object, vHead) != 0)
			return;

		if (CF_ENTRY::Instance()->pLTCSBase->GetObjectBoxMin(pEnemy->Object, vFoot) != 0)
			return;

		if (!this->engine_->WorldToScreen(&vHead, &vHead) && !this->engine_->WorldToScreen(&vFoot, &vFoot))
			continue;

		if (Status) {
			//this->Box2D(vHead, vFoot, COLOR_WHITE);
			this->DrawSkeleton(pEnemy->Object, ESP_COLOR);
		}
	};
}
