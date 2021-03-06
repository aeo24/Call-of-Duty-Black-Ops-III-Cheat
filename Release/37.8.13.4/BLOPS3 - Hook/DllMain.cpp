/*
Game: Call Of Duty Black Ops 3
*/

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <MinHook.h>
#include <stdio.h>
#include <math.h>
#include "GlobalVars.h"
#include "Rendering.h"
#include "Esp.h"
#include "Radar.h"
#include "HealthBar.h"
#include "Menu.h"

#include <iostream>

#if defined _M_X64
#pragma comment(lib, "libMinHook-x64-v120-mdd.lib")
#endif
bool firstRun = true;

void InitVars()
{
	//Radar::Instance()->Init(10.f, 10.f, 200.f, 200.f);
	//CODEngine::RegisterTags();
}

int __fastcall hCG_Draw2D(int localClientNum)
{
	int val = pCG_Draw2D(localClientNum);
	if (firstRun)
	{
		//InitVars();
		firstRun = false;
	}
	//Menu::Instance()->Update();
	

	//std::cout << "Clientinfo: " << CODEngine::GetClientInfo(0) << std::endl;
	//std::cout << "CGT" << CODEngine::GetCGT() << std::endl;
	//std::cout << "" << CODEngine::GetEntity(0) << std::endl;
	float color[4] = { 1.f, 0.64f, 0.f, 1.f };
	float color2[4] = { 0.f, 0.f, 1.f, 1.f };
	float color3[4] = { 1.f, 0.f, 0.f, 1.f };	
	float color4[4] = { 0.f, 1.f, 0.f, 1.f }; 
	//Rendering::Instance()->DrawBox(10, 10, 75, 100, color);
	return val;
}

void startConsole()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
}

BOOL Init()
{
	startConsole();

	if (MH_Initialize() != MH_OK) {
		printf("Init failed!\n");
		return 1;
	}

	//CG_Draw2D
	if (MH_CreateHook((LPVOID)(OFFCG_Draw2D), &hCG_Draw2D, reinterpret_cast<LPVOID*>(&pCG_Draw2D)) != MH_OK) {
		printf("Hook creation failed! %d\n", MH_CreateHook((LPVOID)(OFFCG_Draw2D), &hCG_Draw2D, reinterpret_cast<LPVOID*>(&pCG_Draw2D)));
		return 1;
	}

	if (MH_EnableHook((LPVOID)(OFFCG_Draw2D)) != MH_OK) {
		printf("Hook enable failed %d!\n", MH_EnableHook((LPVOID)(OFFCG_Draw2D)));
		return 1;
	}

	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&Init, NULL, NULL, NULL);
		break;
	default:
		break;
	}

	return TRUE;
}