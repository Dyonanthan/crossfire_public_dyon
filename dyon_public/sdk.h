#include "stdafx.h"
//#include "LTVector.h"

#define ADDR_CROSSFIRE_ENGINE 0x11B71FC // https://www.mpgh.net/forum/showthread.php?t=1324781
#define OFFSET_PLAYERSIZE   0xD80
#define OFFSET_PLAYERSTART  0x208

class ICLTClient;
class ILTCSBase;
class IClientShellStub;
class CF_ENTRY;
struct IntersectInfo;
struct IntersectQuery;

using End3DFn = unsigned int(__cdecl*)(unsigned int);
using FlipScreenFn = unsigned int(__cdecl*)(unsigned int);

using ObjectFilterFn = bool(*)(int*, void*);
using _IntersectSegment = bool(__cdecl*)(IntersectQuery&, IntersectInfo*);

typedef unsigned int HMODELPIECE;
#define INVALID_MODEL_PIECE		((HMODELPIECE)-1)
typedef unsigned int HMODELNODE;
#define INVALID_MODEL_NODE		((HMODELNODE)-1)
typedef unsigned int HMODELSOCKET;
#define INVALID_MODEL_SOCKET	((HMODELSOCKET)-1)

template< class type > type GetVFunction(PVOID base, SIZE_T index)
{
	ULONG_PTR* vtablefunc = *(PDWORD_PTR*)base;

	return (type)(vtablefunc[index]);
}
struct LTRotation
{
	float Quad[4];
};
struct LTransform
{
	D3DXVECTOR3	m_vPos;
	LTRotation	m_rRot;
	float		m_fScale;
};
class ICLTClient
{
public:
	bool IntersectSegment(IntersectQuery& iQuery, IntersectInfo* qInfo)
	{
		using IntersectSegment_t = bool(__cdecl*)(IntersectQuery&, IntersectInfo*);
		DWORD ptr = ((DWORD)this + 0x84);
		return reinterpret_cast<IntersectSegment_t>(ptr)(iQuery, qInfo);
	}
}; //Size: 0x0044
class CLTModel //https://www.mpgh.net/forum/showthread.php?t=1435637
{
public:
	signed int GetSocket2(int *hObj, const char *pSocketName, HMODELSOCKET &hSocket)
	{
		typedef signed int(__thiscall* GetSocket2Fn)(void*, int *hObj, const char *pSocketName, HMODELSOCKET &hSocket);
		return GetVFunction<GetSocket2Fn>(this, 6)(this, hObj, pSocketName, hSocket);
	}
	signed int GetSocket(int *hObj, const char *pSocketName, HMODELSOCKET &hSocket){
		typedef signed int(__thiscall* GetSocketFn)(void*, int *hObj, const char *pSocketName, HMODELSOCKET &hSocket);
		return GetVFunction<GetSocketFn>(this, 7)(this, hObj, pSocketName, hSocket);
	}
	signed int GetSocketTransform(int *hObj, HMODELSOCKET hSocket, LTransform &transform, bool bWorldSpace){
		typedef signed int(__thiscall* GetSocketTransformFn)(void*, int *hObj, HMODELSOCKET hSocket, LTransform &transform, bool bWorldSpace);
		return GetVFunction<GetSocketTransformFn>(this, 8)(this, hObj, hSocket, transform, bWorldSpace);
	}
	signed int GetPiece(int *hObj, const char *pPieceName, HMODELPIECE &hPiece){
		typedef signed int(__thiscall* GetPieceFn)(void*, int *hObj, const char *pPieceName, HMODELPIECE &hPiece);
		return GetVFunction<GetPieceFn>(this, 10)(this, hObj, pPieceName, hPiece);
	}
	signed int GetPieceHideStatus(int *hObj, HMODELPIECE hPiece, bool &bHidden){
		typedef signed int(__thiscall* GetPieceHideStatusFn)(void*, int *hObj, HMODELPIECE hPiece, bool &bHidden);
		return GetVFunction<GetPieceHideStatusFn>(this, 11)(this, hObj, hPiece, bHidden);
	}
	signed int SetPieceHideStatus(int *hObj, HMODELPIECE hPiece, bool bHidden){
		typedef signed int(__thiscall* SetPieceHideStatusFn)(void*, int *hObj, HMODELPIECE hPiece, bool bHidden);
		return GetVFunction<SetPieceHideStatusFn>(this, 12)(this, hObj, hPiece, bHidden);
	}
	signed int GetNode(int *hObj, const char *pNodeName, UINT &hNode){
		typedef signed int(__thiscall* GetNodeFn)(void*, int *hObj, const char *pNodeName, UINT &hNode);
		return GetVFunction<GetNodeFn>(this, 13)(this, hObj, pNodeName, hNode);
	}
	signed int GetNodeName(int *hObj, UINT hNode, char *name, unsigned int maxlen){
		typedef signed int(__thiscall* GetNodeNameFn)(void*, int *hObj, UINT hNode, char *name, unsigned int maxlen);
		return GetVFunction<GetNodeNameFn>(this, 14)(this, hObj, hNode, name, maxlen);
	}
	signed int GetNodeTransform(int *hObj, UINT hNode, LTransform &transform, bool bWorldSpace){
		typedef signed int(__thiscall* GetNodeTransformFn)(void*, int *hObj, UINT hNode, LTransform &transform, bool bWorldSpace);
		return GetVFunction<GetNodeTransformFn>(this, 15)(this, hObj, hNode, transform, bWorldSpace);
	}
	signed int GetNextNode(int *hObj, unsigned int hNode, unsigned int &pNext){
		typedef signed int(__thiscall* GetNextNodeFn)(void*, int *hObj, unsigned int hNode, unsigned int &pNext);
		return GetVFunction<GetNextNodeFn>(this, 16)(this, hObj, hNode, pNext);
	}
	signed int GetNumChildren(int *hObj, unsigned int hNode, unsigned int &NumChildren){

		typedef signed int(__thiscall* GetNumChildrenFn)(void*, int *hObj, unsigned int hNode, unsigned int &NumChildren);
		return GetVFunction<GetNumChildrenFn>(this, 18)(this, hObj, hNode, NumChildren);
	}
	signed int GetChild(int *hObj, unsigned int parent, unsigned int index, unsigned int &child){
		typedef signed int(__thiscall* GetChildFn)(void*, int *hObj, unsigned int parent, unsigned int index, unsigned int &child);
		return GetVFunction<GetChildFn>(this, 19)(this, hObj, parent, index, child);
	}
	signed int GetParent(int *hObj, unsigned int node, unsigned int &parent){

		typedef signed int(__thiscall* GetParentFn)(void*, int *hObj, unsigned int node, unsigned int &parent);
		return GetVFunction<GetParentFn>(this, 20)(this, hObj, node, parent);
	}
	signed int GetNumNodes(int *hObj, unsigned int &num_nodes){

		typedef signed int(__thiscall* GetNumNodesFn)(void*, int *hObj, unsigned int &num_nodes);
		return GetVFunction<GetNumNodesFn>(this, 21)(this, hObj, num_nodes);
	}
};
class ILTCSBase : public ICLTClient
{
public:
	CLTModel* GetLTModel()
	{
		typedef CLTModel*(__thiscall* oGetLTModel)(void *);
		return GetVFunction<oGetLTModel>(this, 4)(this);
	}
	uint32_t GetObjectPos(int* hObj, D3DXVECTOR3 *pPos)
	{
		typedef uint32_t(__thiscall* oGetObjectPos)(void*, int*, D3DXVECTOR3*);
		return GetVFunction<oGetObjectPos>(this, 39)(this, hObj, pPos);
	}
	uint32_t GetObjectBoxMin(int* hObj, D3DXVECTOR3 &mins)
	{
		typedef uint32_t(__thiscall* oGetObjectBoxMin)(void*, int*, D3DXVECTOR3 &);
		return GetVFunction<oGetObjectBoxMin>(this, 140)(this, hObj, mins);
	}
	uint32_t GetObjectBoxMax(int* hObj, D3DXVECTOR3 &maxs)
	{
		typedef uint32_t(__thiscall* oGetObjectBoxMax)(void*, int*, D3DXVECTOR3 &);
		return GetVFunction<oGetObjectBoxMax>(this, 141)(this, hObj, maxs);
	}
};
class CLocalClient
{
public:
	float GetYaw(){
		return *(float *)((uintptr_t)this + 0x00);
	}
	float GetPitch()
	{
		return *(float *)((uintptr_t)this + 0x00);
	}
};
class IClientShellStub
{
public:
	CLocalClient* getLocalClient(){
		return (CLocalClient*)((DWORD)this + 0x78);
	}
}; //Size: 0x0044
class CF_ENTRY
{
public:
	ILTCSBase* pLTCSBase; //0x0000
	char pad_0004[20]; //0x0004
	IClientShellStub* pClientShellStub; //0x0018

public:
	static CF_ENTRY* Instance()
	{
		return (CF_ENTRY*)ADDR_CROSSFIRE_ENGINE;
	}
}; //Size: 0x0040
class CGameCon
{
public:
	char pad_0000[16]; //0x0000
	int32_t PhatomLight; //0x0010 value 50
	char pad_0014[144]; //0x0014
	int32_t WallHack; //0x00A4 original value 16777217
	char pad_00A8[12]; //0x00A8
	int32_t SeeGhost; //0x00B4 original value 5
	char pad_00B8[4032]; //0x00B8
}; //Size: 0x1078
class CEntity
{
public:
	char pad_0000[8]; //0x0000
	int* Object; //0x0008
	int8_t ClientID; //0x000C
	int8_t Team; //0x000D
	char Name[12]; //0x000E
	char pad_001A[2]; //0x001A
	int* CharacterFX; //0x001C
	__int32 iPlayerSlotTeam; //0x0020
	char pad_0024[4]; //0x0024
	__int32 Has_C4; //0x0028
	char pad_002C[24]; //0x002C
	int8_t iHealth; //0x0044
	char pad_0045[1]; //0x0045
	int8_t Kills; //0x0046
	char pad_0047[1009]; //0x0047
}; //Size: 0x0074
struct IntersectInfo
{
	D3DXVECTOR3 vImpactPos;	//0x0000
	char _UnkSpace[16];			//SPACE
	int* hObjImpact;	//0x001C
	DWORD m_hPoly;			//0x0020
	DWORD m_SurfaceFlags;	//0x0024
	DWORD m_hNode;			//0x0028
};
struct IntersectQuery
{
	D3DXVECTOR3 From;					//0x0000
	D3DXVECTOR3 To;						//0x000C
	char _UnkSpace[12];						//SPACE
	unsigned int Flags;					//0x0024
	ObjectFilterFn FilterFn;			//0x0028
	void* FilterIntersectParam;			//0x002C
	ObjectFilterFn FilterIntersectFn;	//0x0030
	void* FilterParam;					//0x0034
	void* PolyFilterParam;				//0x0038
};