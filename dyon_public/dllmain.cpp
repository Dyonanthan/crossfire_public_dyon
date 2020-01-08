// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "esp.h"
#include "hook.h"
#include "engine.h"
#include "log.h"
Log* file_log = new Log("dyon_public.log", true);
Engine* g_Engine = new Engine(file_log);
ESP* g_ESP = new ESP(g_Engine);
//695340 get ClientID
uint32_t original_flipscreen;
uint32_t original_zmfunction;
__declspec(naked) void HookedZMFunction()
{
	DWORD _esi;
	_asm
	{
		pushad
		pushfd
		MOV _esi, ESI
	}
	std::cout << "AI: " << _esi << std::endl;
	_asm
	{
		popfd
		popad
		jmp original_zmfunction
	}
}

__declspec(naked) void HookedFlipScreen()
{
	_asm
	{
		pushad
		pushfd
	}

	g_Engine->Run();
	g_ESP->InitPvP(g_Engine->esp_status_);
	_asm
	{
		popfd
		popad
		jmp original_flipscreen
	}
}

void CALL_HOOK() {

	AllocConsole();
	SetConsoleTitleA("CROSSFIRE");
	AttachConsole(GetCurrentProcessId());

	FILE* pFile = nullptr;
	freopen_s(&pFile, "CON", "r", stdin);
	freopen_s(&pFile, "CON", "w", stdout);
	freopen_s(&pFile, "CON", "w", stderr);

	file_log->Write("Initializing pointers...");

	while (g_Engine->Init() == false)
		Sleep(300);
		
	g_Engine->HookFlipScreen(reinterpret_cast<uint32_t>(&HookedFlipScreen), &original_flipscreen);
	g_Engine->HookZMFunction(reinterpret_cast<uint32_t>(&HookedZMFunction), &original_zmfunction);

}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		file_log->Write("Entry point called with DLL_PROCESS_ATTACH.");
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CALL_HOOK, hModule, NULL, NULL);
	case DLL_PROCESS_DETACH:
		// file_log->Write("Entry point called with DLL_PROCESS_DETACH.");
		//file_log->Close();
		break;
	}
	return TRUE;
}

