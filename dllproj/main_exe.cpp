#include <windows.h>
#include <sysinfoapi.h>
#include <stdio.h>

#include <iostream>
#include <sstream>
#include <vector>
using std::vector;
using std::string;

HINSTANCE hInst;

typedef void (*f_helloFromDll)(HWND);

f_helloFromDll helloFromDll;

typedef void (*f_helloFromDll1)(HWND);

f_helloFromDll1 helloFromDll1;

#define MSG(x) MessageBoxA(hwnd, x, "", MB_OKCANCEL)
#define MSGW(x) MessageBoxW(hwnd, x, L"", MB_OKCANCEL)

void helloFromExe(HWND hwnd)
{
	MessageBoxA(hwnd, "hello from exe!", "", MB_OKCANCEL);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	hInst = hInstance;

	WNDCLASS wC;

	wC.cbClsExtra = 0;
	wC.cbWndExtra = 0;
	wC.hbrBackground = NULL;
	wC.hInstance = hInst;
	wC.hCursor = LoadCursor(NULL, IDC_ARROW);
	wC.hIcon= LoadIcon(NULL, IDI_APPLICATION);
	wC.lpszClassName = "Main";
	wC.lpfnWndProc = DefWindowProcW;
	wC.lpszMenuName = NULL;
	wC.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wC);

	HWND hwnd = CreateWindow("Main", "Main", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

	ShowWindow(hwnd, SW_SHOW);

	UpdateWindow(hwnd);

	HINSTANCE hdll = LoadLibraryA(".\\dllprojdll.dll");

	if (!hdll) {
		string s("could not load the dynamic library ");
		s += GetLastError();

		MSG(s.c_str());
		return EXIT_FAILURE;
	}

	helloFromDll = (f_helloFromDll)GetProcAddress(hdll, "helloFromDll");
	if (!helloFromDll) {
		MSG("could not locate the function helloFromDll");
		goto out;
	}

	helloFromDll1 = (f_helloFromDll)GetProcAddress(hdll, "helloFromDll1");
	if (!helloFromDll1) {
		MSG("could not locate the function helloFromDll1");
		goto out;
	}

	printf("dll base addr = %08x\n", reinterpret_cast<std::uint32_t>(helloFromDll) - 0x70);
	printf("helloFromDll addr = %08x\n", reinterpret_cast<std::uint32_t>(helloFromDll));
	printf("helloFromDll1 addr = %08x\n", reinterpret_cast<std::uint32_t>(helloFromDll1));
	printf("helloFromExe addr = %08x\n", reinterpret_cast<std::uint32_t>(helloFromExe));

	helloFromDll(hwnd);

	while (true)
	{
		PeekMessage(&msg, NULL, 0, 0, 0);
		if (!GetMessage(&msg, 0, 0, 0))
			return 0;
		DispatchMessage(&msg);
	}

out:
	FreeLibrary(hdll);

	return msg.wParam;
}