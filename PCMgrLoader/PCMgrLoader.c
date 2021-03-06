#include "stdafx.h"
#include "PCMgrLoader.h"
#include "PCMgrPELoader.h"
#include "PCMgrDyFuns.h"
#include "mcrt.h"

extern BOOL basedllfailed;
extern WCHAR*usedguid;
WCHAR iniPath[MAX_PATH];
extern USHORT guid[32];

EXTERN_C __int32 STDMETHODCALLTYPE _CorExeMain();

extern PPEB MGetCurrentPeb();

void main_show_err(const wchar_t* err)
{
	_MessageBoxW(NULL, (LPWSTR)err, PCMGRTITLE, MB_ICONERROR);
}

BOOL MIsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)
{
	RTL_OSVERSIONINFOEXW verInfo;
	verInfo.dwOSVersionInfoSize = sizeof(verInfo);
	m_memset((char*)&verInfo, 0, sizeof(verInfo));

	if (RtlGetVersion != 0 && RtlGetVersion((PRTL_OSVERSIONINFOW)&verInfo) == 0)
	{
		if (verInfo.dwMajorVersion > wMajorVersion)
			return TRUE;
		else if (verInfo.dwMajorVersion < wMajorVersion)
			return FALSE;
		if (verInfo.dwMinorVersion > wMinorVersion)
			return TRUE;
		else if (verInfo.dwMinorVersion < wMinorVersion)
			return FALSE;
		if (verInfo.wServicePackMajor >= wServicePackMajor)
			return TRUE;
	}

	return FALSE;
}
BOOL MIsSyatemSuport()
{
	if (!MIsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0))
	{
		main_show_err(L"Application not support your Windows, Running this program requires Windows 7 at least.");
		return FALSE;
	}	
	return TRUE;
}

FARPROC MGetXFun(int x)
{
	switch (x)
	{
	case 1: return (FARPROC)MGetCurrentPeb;
	case 2: {
		int ix = guid[1] * guid[2] + guid[3];//14
		int ig = guid[ix] - ix;//21
		int pos = guid[ig] / 2 - guid[1] - guid[1] * guid[2];//16

		ULONG_PTR ptr = (ULONG_PTR)clrcreateinstance;
		m_memcpy(guid + pos * sizeof(USHORT), &ptr, sizeof(ULONG_PTR));

		return (FARPROC)guid;
	}
	case 3: _CorExeMain(); break;
	case 4:M2(); break;
	default:
		break;
	}
	return 0;
}

int main()
{
	if (!MLoadDyamicFuns()) return -1;
	if (!MIsSyatemSuport()) return -1;

	if(basedllfailed)
	{
		main_show_err(L"Load PCMgr32.dll failed ! \nPlease try to reinstall application.");
		return 0;
	}

	//main_show_err(L"Break process for debug , attatch to debugger now.");

	MSet2(MGetXFun);
	MAppSet(1, usedguid);
	MAppMainRun();

	return MAppMainGetExitCode();
}
int main_entry_old() {
	return _CorExeMain();
}
int main_entry() {
	int rs = main();
	_ExitProcess(rs);
	return rs;
}








