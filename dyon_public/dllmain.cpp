// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "esp.h"
#include "hook.h"
#include "engine.h"
#include "log.h"
Log* file_log = new Log("dyon_public.log", true);
Engine* g_Engine = new Engine(file_log);
ESP* g_ESP = new ESP(g_Engine);

uint32_t original_flipscreen;

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
	file_log->Write("Initializing pointers...");

	while (g_Engine->Init() == false)
		Sleep(300);
		
	g_Engine->HookFlipScreen(reinterpret_cast<uint32_t>(&HookedFlipScreen), &original_flipscreen);

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
		// file_log->Close();
		break;
	}
	return TRUE;
}

