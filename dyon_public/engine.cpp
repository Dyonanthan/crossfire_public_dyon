#include "engine.h"
#include "memory.h"

Engine::Engine(Log* log)
{
	this->file_log_ = log;
	this->menu_ = new Menu();

	// build menu
	this->file_log_->Write("Building menu.");
	char *option_on_off[] = { "Off", "On" };
	char *option_golden_normal[] = { "Off", "Golden", "Normal" };
	junkasm
	char *option_knife_speed[] = { "Off", "2x", "4x", "6x" };
	char *option_knife_range[] = { "Off", "250", "350", "500" };
	char *option_movespeed_penalty[] = { "Off", "115%", "125%", "145%" };
	this->menu_->AddItem(&this->esp_status_, "ESPs", option_on_off, 2);
	this->menu_->AddItem(&this->no_recoil_status_, "No recoil", option_on_off, 2);
	junkasm
	this->menu_->AddItem(&this->wallhack_status_, "Wallhack", option_on_off, 2);
	this->menu_->AddItem(&this->seeghost_status_, "See ghost", option_on_off, 2);
	this->menu_->AddItem(&this->phantom_status_, "Phantom Chams", option_on_off, 2);
}
bool Engine::Init() {
	this->hCShell = GetModuleHandleA("CShell.dll");

	if (this->hCShell == NULL)
		return false;

	this->cshell_base_ = reinterpret_cast<uint32_t>(this->hCShell);

	MODULEINFO mi;

	this->hClientFxD = GetModuleHandleA("ClientFx.fxd");

	if (this->hClientFxD == NULL)
		return false;

	if (GetModuleInformation(GetCurrentProcess(), this->hCShell, &mi, sizeof(mi)) == FALSE)
		return false;

	this->file_log_->Writef("CShell base address: 0x%X", this->cshell_base_);

	this->flipscreen_ = FindPattern(this->cshell_base_, 0xFFFFFF, reinterpret_cast<uint8_t*>("\x56\x8B\xF1\x80\x7E\x34\x00\x74\x7D"), "xxxxxxxxx");
	this->call_to_flipscreen_ = FindPattern(this->cshell_base_, 0xFFFFFF, reinterpret_cast<uint8_t*>("\xE8\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xC6\x46\x38\x00"), "x????xx????x????xxxx");
	
	if (!this->flipscreen_ || !this->call_to_flipscreen_)
		return false;

	this->file_log_->Writef("Address of FlipScreen function: 0x%X", this->flipscreen_);
	this->file_log_->Writef("Call to FlipScreen function: 0x%X", this->call_to_flipscreen_);

	this->deviceGame_ = *reinterpret_cast<uint32_t*>(FindPattern(0x400000, 0xFFFFFF, reinterpret_cast<uint8_t*>("\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00"), "x????x????xx????????") + 1);
	this->file_log_->Writef("Address of DeviceGame: 0x%X", this->deviceGame_);

	this->address_of_cGame = *reinterpret_cast<uint32_t*>(FindPattern(0x400000, 0xFFFFFF, reinterpret_cast<uint8_t*>("\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x06\x8B\x50\x18"), "x????x????xxxxx") + 1);
	this->file_log_->Writef("Address of CGameCon: 0x%X", this->address_of_cGame);

	this->address_of_intersect_ = (uint32_t)(FindPattern(0x400000, 0xFFFFFF, reinterpret_cast<uint8_t*>("\x5D\xC3\xCC\x55\x8B\xEC\x8B\x45\x0C\x50\x8B\x4D\x08\x51\x8B\x15\x00\x00\x00\x00"), "xxxxxxxxxxxxxxxx????") + 3);
	this->file_log_->Writef("Address of IntersectSegment: 0x%X", this->address_of_intersect_);

	this->getlocalplayer_ = FindPattern(this->cshell_base_, 0xFFFFFF, reinterpret_cast<uint8_t*>("\x56\x8B\xF1\x0F\xB6\x86\x00\x00\x00\x00\x50\xE8\x00\x00\x00\x00\x83\xC4\x04\x84\xC0\x75\x04"), "xxxxxx????xx????xxxxxxx");
	this->file_log_->Writef("Address of GetLocalPlayer Func: 0x%X", this->getlocalplayer_);

	this->zmfunction_ = (uint32_t)(FindPattern(this->cshell_base_, 0xFFFFFF, reinterpret_cast<uint8_t*>("\x8B\x0D\x00\x00\x00\x00\x8B\x89\x00\x00\x00\x00\x85\xC9\x74\x10"), "xx????xx????xxxx") - 0x19);
	this->call_to_zmfunction_ = (uint32_t)(FindPattern(this->cshell_base_, 0xFFFFFF, reinterpret_cast<uint8_t*>("\x57\xFF\xD2\x8B\xCE\xE8\x00\x00\x00\x00\x8D\x8E\x00\x00\x00\x00"), "xxxxxx????xx????") + 5);

	if (!this->zmfunction_ || !this->call_to_zmfunction_)
		return false;

	this->file_log_->Writef("Address of ZM function: 0x%X", this->flipscreen_);
	this->file_log_->Writef("Call to ZM function: 0x%X", this->call_to_flipscreen_);

	this->initialized_ = true;
	return true;
}
__declspec(noinline) IDirect3DDevice9* Engine::GetDevice()
{
	DWORD *dwPointer = (DWORD *)this->deviceGame_;

	if (!dwPointer)
		return NULL;

	if (!*dwPointer)
		return NULL;

	DWORD *dwPointerTwo = (DWORD *)*dwPointer;

	if (!dwPointerTwo)
		return NULL;

	if (!*dwPointerTwo)
		return NULL;

	return (IDirect3DDevice9 *)*dwPointerTwo;
}
__declspec(noinline) bool Engine::WorldToScreen(D3DXVECTOR3 *vWorldLocation, D3DXVECTOR3 *vScreenCoord)
{
	if (!vWorldLocation || !vScreenCoord)
		return false;

	D3DXMATRIX vecProj;
	D3DXMATRIX vecView;
	D3DXMATRIX vecWorld;

	D3DVIEWPORT9 viewPort;
	HRESULT hVP = this->GetDevice()->GetViewport(&viewPort);
	HRESULT hTV = this->GetDevice()->GetTransform(D3DTS_VIEW, &vecView);
	HRESULT hTP = this->GetDevice()->GetTransform(D3DTS_PROJECTION, &vecProj);
	HRESULT hTW = this->GetDevice()->GetTransform(D3DTS_WORLD, &vecWorld);

	if (FAILED(hVP) || FAILED(hTV) || FAILED(hTP) || FAILED(hTW))
		return false;

	D3DXVec3Project(
		vScreenCoord, vWorldLocation,
		&viewPort, &vecProj, &vecView, &vecWorld);

	return (vScreenCoord->z < 1.f);
}
__declspec(noinline) DWORD Engine::getLocalPlayerFunc()
{
	return this->getlocalplayer_;
}
__declspec(noinline) DWORD Engine::getIntersectSegment()
{
	return this->address_of_intersect_;
}
void Engine::HookFlipScreen(uint32_t routine, uint32_t* original)
{
	this->file_log_->Write("Setting up game hook: FlipScreen.");

	// let the caller know what the address of the original flipscreen function is
	*original = this->flipscreen_;

	uint32_t relative_address = routine - this->call_to_flipscreen_ - 5;
	*reinterpret_cast<uint32_t*>(this->call_to_flipscreen_ + 1) = relative_address;
}

void Engine::HookZMFunction(uint32_t routine, uint32_t* original)
{
	this->file_log_->Write("Setting up game hook: ZM.");

	// let the caller know what the address of the original flipscreen function is
	*original = this->zmfunction_;

	uint32_t relative_address = routine - this->call_to_zmfunction_ - 5;
	*reinterpret_cast<uint32_t*>(this->call_to_zmfunction_ + 1) = relative_address;
}
void Engine::Run()
{
	// navigate through menu and render it
	this->menu_->Navigate();
	junkasm
		this->menu_->Render(this->GetDevice());

	//wallhack, seeghost & phantom
	CGameCon *pGameCon = (CGameCon*)(this->address_of_cGame);

	pGameCon->WallHack = this->wallhack_status_ ? 0 : 16777217;
	pGameCon->SeeGhost = this->seeghost_status_ ? 3 : 5;
	pGameCon->PhatomLight = this->phantom_status_ ? 50 : 2;
}

bool __cdecl Engine::IsVisible(D3DXVECTOR3 MePos, D3DXVECTOR3 TargetPos)
{
	static IntersectQuery iQuery;
	static IntersectInfo iInfo;
	IntersectSegment = (_IntersectSegment)(this->getIntersectSegment());

	if (IntersectSegment != NULL)
	{
		iQuery.From = MePos;
		iQuery.To = TargetPos;
		return !IntersectSegment(iQuery, &iInfo);
	}
	return false;
}