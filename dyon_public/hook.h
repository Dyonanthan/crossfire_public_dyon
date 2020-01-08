#include "stdafx.h"

// Authored by Tristan aka HylianTimelord
// Posted for my dudes @ unknowncheats.me
// Creds to IAmDaz for suggesting memcpy & void*

//https://www.unknowncheats.me/forum/c-and-c-/188449-vmt-hooking-class.html

#pragma once

#include <Windows.h>
#include <map>

using namespace std;

class VMTHook
{
public:

	void** vmt = nullptr; // Pointer to the VMT, we're using it more as an array of void*

	VMTHook(void* vmt); // Hook original VMT by it's address
	VMTHook(DWORD64* vmt_ptr); // Create Shadow VMT from VMT pointer ( Not implemented here )
	~VMTHook(); // Destructor, removes all hooks

	void* Hook(int index, void* hk);
	void ClearHooks();
private:
	map<int, void*>::iterator func_iterator; // Iterator so we can iterate the map below
	map<int, void*> hooked_funcs; // std::map which holds the index hooked and the original function's address
};
