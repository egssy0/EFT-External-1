#include <Windows.h>
#include <iostream>
#include <d3d9.h>
#include <vector>
#include <string>
#include "Utils/Xor.h"
#include "Utils/Utils.h"
#include "Overlay/Overlay.h"
#include "DriverControl/DriverControl.h"
#include "CheatSDK/Offsets.h"
#include "CheatSDK/CheatSDK.h"
#include <thread>
#include "DriverBytes.h"
#include "shitmapper/intel_driver.hpp"
#include "shitmapper/mapper.hpp"
#include "Menu.h"
c_menu_framework* menu_framework = new c_menu_framework;
ProcCBACAPC NtConvertBetweenAuxiliaryCounterAndPerformanceCounter;
CheatGlobalData* SDKGlobalData = nullptr;
bool ExGetProcessId(_Out_ LPDWORD lpdwProcessId, HWND* Hwnd)
{
	HWND GameHwnd = FindWindowW(xor(L"UnityWndClass"), xor(L"EscapeFromTarkov"));
	if (GameHwnd != NULL)
	{
		GetWindowThreadProcessId(GameHwnd, lpdwProcessId);
		*Hwnd = GameHwnd;
		return true;
	}
	return false;
}

void drawLoop(int width, int height)
{
	menu_framework->do_menu_controls();
	
}

void OverlaySetup()
{
	DirectOverlaySetup(drawLoop, FindWindow(NULL, "EscapeFromTarkov"));
}

int main()
{
	SetConsoleTitle("");

	
	auto module = (LoadLibraryW)(xor(L"ntdll.dll"));
	if (!module)
	{
		return FALSE;
	}
	NtConvertBetweenAuxiliaryCounterAndPerformanceCounter = (ProcCBACAPC)GetProcAddress(module, xor("NtConvertBetweenAuxiliaryCounterAndPerformanceCounter"));
	HWND Hwnd = 0;
	DWORD ProcId = 0;
	std::thread(OverlaySetup).detach();
	if (!Driver.IsDriverLoaded())
	{
		std::cout << ("Driver loading....") << std::endl;
		Sleep(1000);
		HANDLE iqvw64e_device_handle = intel_driver::Load();
		if (iqvw64e_device_handle == INVALID_HANDLE_VALUE)
		{
			std::cout << ("[ - ] Failed #1") << std::endl;
			
		}
		
		if (!mapper::Driver(iqvw64e_device_handle, Bytes, sizeof(Bytes)))
		{
			std::cout << ("[ - ] Failed #2") << std::endl;
			
		}
		intel_driver::Unload(iqvw64e_device_handle);
		std::cout << ("Succes") << std::endl;
	}

	
	

	SDKGlobalData = static_cast<CheatGlobalData*>(VirtualAlloc(NULL, sizeof(CheatGlobalData), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
	if (!SDKGlobalData)
		return 0;

	Sleep(3000);
	Driver.SetPID(ProcId);
	uintptr_t UnityPlayer = Driver.GetModInfo(xor ("UnityPlayer.dll")).ModBase;
	std::cout << xor ("UnityPlayer: \t") << UnityPlayer << std::endl;
	SDKGlobalData->GameObjManager = Driver.Read<uintptr_t>(UnityPlayer + UNITY_OBJECT_LIST);
	SDKGlobalData->SpeedHackData = Driver.Read<uintptr_t>(UnityPlayer + UNITY_TIME_SCALE + (7 * 8));

	Sleep(100);
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(ColectThreadData), NULL, 0, 0);
	Sleep(100);
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(MiscThreadData), NULL, 0, 0);
	Sleep(100);
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(AimThreadData), NULL, 0, 0);
	MemThread();
	
	return 0;
	
	
}
