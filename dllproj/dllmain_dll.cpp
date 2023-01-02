#include <windows.h>
#include <cstdio>

void DisplayConsole()
{
	if (AllocConsole())
	{
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
}

extern "C"
{
	__declspec(dllexport) void helloFromDll(HWND hwnd);
	__declspec(dllexport) void helloFromDll1(HWND hwnd);
};

void helloFromDll(HWND hwnd)
{
	MessageBoxA(hwnd, "hello from dll!", "", MB_OKCANCEL);
}

void helloFromDll1(HWND hwnd)
{
	MessageBoxA(hwnd, "hello from dll! 1", "", MB_OKCANCEL);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisplayConsole();
		break;
	}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}