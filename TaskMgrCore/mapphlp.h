#pragma once
#include "stdafx.h"
#include "ntdef.h"

typedef void(__cdecl *exitcallback)();
typedef int(__cdecl *taskdialogcallback)(HWND hwnd, LPWSTR text, LPWSTR title, LPWSTR apptl, int ico, int button);
typedef void(__cdecl *EnumWinsCallBack)(HWND hWnd, HWND hWndParent);
typedef void(__cdecl *GetWinsCallBack)(HWND hWnd, HWND hWndParent, int i);
typedef void(__cdecl *WorkerCallBack)(int msg, void* data1, void* data2);
typedef BOOL(__cdecl *TerminateImporantWarnCallBack)(LPWSTR commandName, int id);

LRESULT MAppWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void MPrintErrorMessage(LPWSTR str, int icon = MB_OK);
int MShowMessageDialog(HWND hwnd, LPWSTR text, LPWSTR title, LPWSTR instruction, int i=0, int button=0);
int MShowErrorMessage(LPWSTR text, LPWSTR intr, int ico=0, int btn=0);
int MShowErrorMessageWithLastErr(LPWSTR text, LPWSTR intr, int ico, int btn);

EXTERN_C M_API BOOL MIsSystemSupport();
EXTERN_C M_API BOOL MAppMainCanRun();
EXTERN_C M_API void MAppMainExit(UINT exitcode);
EXTERN_C M_API DWORD MAppMainGetExitCode();
EXTERN_C M_API void MAppMainRun();

EXTERN_C M_API int MAppMainGetArgs(LPWSTR cmdline);
EXTERN_C M_API LPWSTR MAppMainGetArgsStr(int index);
EXTERN_C M_API void MAppMainGetArgsFreAall();

EXTERN_C M_API void MAppHideCos();
EXTERN_C M_API void* MAppSetCallBack(void* cp, int id);
EXTERN_C M_API void MAppMainCall(int msg, void * data1, void * data2);
EXTERN_C M_API void MAppSetLanuageItems(int in, int ind, LPWSTR msg, int size);
EXTERN_C M_API int MAppRegShowHotKey(HWND hWnd, UINT vkkey, UINT key);
EXTERN_C M_API void MAppSetStartingProgessText(LPWSTR text);
EXTERN_C M_API void MAppExit();
EXTERN_C M_API void MAppRebot();
EXTERN_C M_API void MAppRebotAdmin();
EXTERN_C M_API void MAppRebotAdmin2(LPWSTR agrs);
EXTERN_C M_API void MListDrawItem(HWND hWnd, HDC hdc, int x, int y, int w, int h, int state);
EXTERN_C M_API BOOL MAppStartEnd();
EXTERN_C M_API BOOL MAppStartTryCloseLastApp(LPWSTR windowTitle);
EXTERN_C M_API BOOL MAppKillOld(LPWSTR procName);
EXTERN_C M_API BOOL MAppStartTest();
EXTERN_C M_API void MAppWorkCall2(UINT msg, WPARAM wParam, LPARAM lParam);
EXTERN_C M_API int MAppWorkCall3(int id, HWND hWnd, void*data);
EXTERN_C M_API HICON MGetWindowIcon(HWND hWnd);

#define MStrEqual MStrEqualW
#define MStrAdd MStrAddW
#define A2W MConvertLPCSTRToLPWSTR
#define W2A MConvertLPWSTRToLPCSTR

EXTERN_C M_API void MConvertStrDel(void * str);

EXTERN_C M_API LPWSTR MConvertLPCSTRToLPWSTR(const char * szString);
EXTERN_C M_API LPCSTR MConvertLPWSTRToLPCSTR(const WCHAR * szString);
EXTERN_C M_API LPWSTR cMStrLoW(const LPWSTR str);
EXTERN_C M_API LPWSTR MStrUpW(const LPWSTR str);
EXTERN_C M_API LPCSTR MStrUpA(const LPCSTR str);
EXTERN_C M_API LPWSTR MStrLoW(const LPWSTR str);
EXTERN_C M_API LPCSTR MStrLoA(const LPCSTR str);
EXTERN_C M_API LPWSTR MStrAddW(const LPWSTR str1, const LPWSTR str2);
EXTERN_C M_API LPCSTR MStrAddA(const LPCSTR str1, const LPCSTR str2);
EXTERN_C M_API BOOL MStrEqualA(const LPCSTR str1, const LPCSTR str2);
EXTERN_C M_API BOOL MStrEqualW(const wchar_t* str1, const wchar_t* str2);
EXTERN_C M_API LPCSTR MIntToStrA(int i);
EXTERN_C M_API LPWSTR MIntToStrW(int i);
EXTERN_C M_API LPCSTR MLongToStrA(long i);
EXTERN_C M_API LPWSTR MLongToStrW(long i);
EXTERN_C M_API int MStrToIntA(char * str);
EXTERN_C M_API int MStrToIntW(LPWSTR str);
EXTERN_C M_API DWORD MStrSplitA(char * str, const LPCSTR splitStr, LPCSTR * result, char ** lead);
EXTERN_C M_API DWORD MStrSplitW(LPWSTR str, const LPWSTR splitStr, LPWSTR * result, wchar_t ** lead);
EXTERN_C M_API BOOL MStrContainsA(const LPCSTR str, const LPCSTR testStr, LPCSTR * resultStr);
EXTERN_C M_API BOOL MStrContainsW(const LPWSTR str, const LPWSTR testStr, LPWSTR * resultStr);
EXTERN_C M_API int MHexStrToIntW(wchar_t *s);
EXTERN_C M_API long long MHexStrToLongW(wchar_t *s);

void ThrowErrorAndErrorCodeX(NTSTATUS code, LPWSTR msg, LPWSTR title, BOOL ntstatus = TRUE);