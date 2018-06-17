// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "resource.h"

HINSTANCE hInst;
extern HICON HIconDef;
extern BOOL LoadDll();
extern void FreeDll();
extern HCURSOR hCurLoading;

EXTERN_C M_API int MGetCpuCount();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hInst = (HINSTANCE)hModule;
		HIconDef = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICONDEFAPP), IMAGE_ICON, 16, 16, 0);
		LoadDll();
		hCurLoading = LoadCursor(NULL, IDC_WAIT);
		MGetCpuCount();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		FreeDll();
		break;
	}
	return TRUE;
}
