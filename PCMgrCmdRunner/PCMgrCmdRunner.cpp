// PCMgrCmdRunner.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "PCMgrCmdRunnerEntry.h"
#include <string>
#include <vector>

#include "..\TaskMgrCore\cmdhlp.h"
#include "..\TaskMgrCore\StringHlp.h"
#include "..\TaskMgrCore\fmhlp.h"
#include "..\TaskMgrCore\mapphlp.h"
#include "..\TaskMgrCore\prochlp.h"
#include "..\TaskMgrCore\ntdef.h"
#include "..\TaskMgrCore\thdhlp.h"
#include "..\TaskMgrCore\suact.h"
#include "..\TaskMgrCore\syshlp.h"
#include "..\TaskMgrCore\loghlp.h"

vector<string> *MAppConsoleInitCommandLine(string * outCmd)
{
	string orgCmd;
	int argc = 0;
	LPWSTR*argsStrs = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (argsStrs) {
		if (argc > 1) {
			vector<string> *cmdArray = new vector<string>();
			for (int i = 1; i < argc; i++)
			{
				LPCSTR str = W2A(argsStrs[i]);
				cmdArray->push_back(string(str));
				orgCmd += str;
				delete str;
			}
			if (outCmd)*outCmd = orgCmd;
			return cmdArray;
		}
		LocalFree(argsStrs);
		return nullptr;
	}
	return nullptr;
}

MCmdRunner *runner = NULL;

CMD_CAPI(VOID) MInitAllCmd()
{
	runner = MGetStaticCmdRunner();

	runner->RegisterCommandNoReturn("?", MRunCmd_Help);
	runner->RegisterCommandNoReturn("help", MRunCmd_Help);
	runner->RegisterCommandNoReturn("tasklist", MRunCmd_TaskList);
	runner->RegisterCommandNoReturn("taskkill", MRunCmd_TaskKill);
	runner->RegisterCommandNoReturn("tasksusp", MRunCmd_TaskSuspend);
	runner->RegisterCommandNoReturn("tasksuspend", MRunCmd_TaskResume);
	runner->RegisterCommandNoReturn("taskresume", MRunCmd_TaskResume);
	runner->RegisterCommandNoReturn("threadkill", MRunCmd_ThreadKill);
}

BOOL cmdThreadCanRun = FALSE;
BOOL cmdThreadRunning = FALSE;
HANDLE hCmdThread = NULL;

void __cdecl MEnumProcessCallBack(DWORD pid, DWORD parentid, LPWSTR exename, LPWSTR exefullpath, int tp, HANDLE hProcess)
{
	if (tp)
	{
		MPrintMumberWithLen(pid, 5);
		printf(" ");
		MPrintMumberWithLen(parentid, 5);
		printf("        ");//6
		MPrintStrWithLenW(exename, 32);
		wprintf_s(L"   %s\n", exefullpath);
	}
}

M_CMD_HANDLER(MRunCmd_TaskList)
{
	wprintf_s(L"PID     ParentPID ProcessName                          FullPath\n");
	MEnumProcess((EnumProcessCallBack)MEnumProcessCallBack, NULL);
}
M_CMD_HANDLER(MRunCmd_Help) {
	printf("Help : \n");
	printf("    tasklist : list all running process\n");
	printf("    taskkill pid [force] [useApc] : kill a running process use process id\n            force : Want to use kernel force kill process\n            useApc : When force kill , should use APC to terminate threads\n");
	printf("    tasksuspend pid [force] : suspend process use process id\n            force : Want to use kernel force suspend process\n");
	printf("    taskresume pid [force] : resume process use process id\n            force : Want to use kernel force resume process\n");
	printf("    toadmin : run pcmgr as adminstrator\n");
	printf("    threadkill tid  [force] [useApc] : kill a running thread use thread id\n            force : Want to use kernel force kill thread\n            useApc : When force kill , should use APC to terminate thread\n");
}
M_CMD_HANDLER(MRunCmd_TaskKill)
{
	if (size < 2) { printf("Please enter pid.\n"); return; }
	DWORD pid = static_cast<DWORD>(atoll((*cmds)[1].c_str()));
	if (pid > 4) {
		if (size > 2 && (*cmds)[2] == "force")
		{
			BOOL useApc = FALSE;
			if (size > 3 && (*cmds)[3] == "apc")useApc = TRUE;
			NTSTATUS status = 0;
			if (M_SU_TerminateProcessPID(pid, 0, &status, useApc) && NT_SUCCESS(status))
				MPrintSuccess();
			else wprintf(L"TerminateProcess Failed %s\n", MNtStatusToStr(status));
		}
		else
		{
			HANDLE hProcess;
			NTSTATUS status = MOpenProcessNt(pid, &hProcess);
			if (status == STATUS_SUCCESS)
			{
				status = MTerminateProcessNt(0, hProcess);
				if (NT_SUCCESS(status)) printf("Success.\n");
				else wprintf(L"TerminateProcess Failed %s\n", MNtStatusToStr(status));
			}
			else wprintf(L"TerminateProcess Failed %s\n", MNtStatusToStr(status));
		}
	}
	else printf("Invalid pid.\n");
}
M_CMD_HANDLER(MRunCmd_ThreadKill)
{
	if (size < 2) { printf("Please enter tid.\n"); return; }
	DWORD tid = static_cast<DWORD>(atoll((*cmds)[1].c_str()));
	NTSTATUS status = 0;
	if (size > 2 && (*cmds)[2] == "force")
	{
		BOOL useApc = FALSE;
		if (size > 3 && (*cmds)[3] == "apc")useApc = TRUE;
		if (!(M_SU_TerminateThreadTID(tid, 0, &status, useApc) && NT_SUCCESS(status)))
			wprintf(L"TerminateThread Failed %s\n", MNtStatusToStr(status));
	}
	else {
		HANDLE hThread;
		DWORD NtStatus = MOpenThreadNt(tid, &hThread, tid);
		if (NT_SUCCESS(status)) {
			NtStatus = MTerminateThreadNt(hThread);
			if (NtStatus == STATUS_SUCCESS)
				printf("Success.\n");
			else wprintf(L"TerminateThread Failed %s\n", MNtStatusToStr(status));
		}
		else wprintf(L"Failed : OpenThread : %s\n", MNtStatusToStr(status));
	}
}
M_CMD_HANDLER(MRunCmd_TaskSuspend)
{
	if (size < 2) { printf("Please enter pid.\n"); return; }
	DWORD pid = static_cast<DWORD>(atoll((*cmds)[1].c_str()));
	if (pid > 4) {
		NTSTATUS status = MSuspendProcessNt(pid, 0);
		if (status == STATUS_SUCCESS)
			MPrintSuccess();
		else wprintf(L"Failed : SuspendProcess : %s\n", MNtStatusToStr(status));
	}
	else printf("Invalid pid.\n");
}
M_CMD_HANDLER(MRunCmd_TaskResume)
{
	if (size < 2) { printf("Please enter pid.\n"); return; }
	DWORD pid = static_cast<DWORD>(atoll((*cmds)[1].c_str()));
	if (pid > 4) {
		NTSTATUS status = MResumeProcessNt(pid, 0);
		if (status == STATUS_SUCCESS)
			MPrintSuccess();
		else wprintf(L"Failed : SuspendProcess :%s\n", MNtStatusToStr(status));
	}
	else printf("Invalid pid.\n");
}

int MAppCmdRunner(BOOL isMain)
{
REENTER:
	printf_s("\n>");

	char maxbuf[260];
	gets_s(maxbuf);

	char *buf = maxbuf;
	if (maxbuf[0] == '>')
		buf = maxbuf + 1;

	if (runner->MRunCmdWithString(maxbuf))
	{
		if (isMain) MAppMainThreadCall(M_MTMSG_COSCLOSE, 0);
		return 0;
	}

	if (cmdThreadCanRun)
		goto REENTER;

	return 0;
}
int MAppCmdStart()
{
	setlocale(LC_ALL, "chs");
	cmdThreadCanRun = TRUE;
	M_LOG_Init_InConsole();

	printf_s("PCMgr Command Line Tool\n");
	printf_s("Version : 1.0.0.1\n\n");
	MGetWindowsBulidVersion();
	printf_s("\n");

	string orgCmd;
	vector<string> * cmds = MAppConsoleInitCommandLine(&orgCmd);

	if (cmds) runner->MRunCmd(cmds, orgCmd.c_str());
	delete(cmds);

	int rs = MAppCmdRunner(FALSE);
	M_LOG_Close_InConsole();
	ExitProcess(rs);
	return rs;
}

DWORD WINAPI MConsoleThread(LPVOID lpParameter)
{
	Sleep(1000);
	return MAppCmdRunner(TRUE);
}

CMD_CAPI(BOOL) MStartRunCmdThread()
{
	if (!cmdThreadRunning)
	{
		cmdThreadCanRun = TRUE;
		hCmdThread = CreateThread(NULL, NULL, MConsoleThread, NULL, NULL, NULL);
		cmdThreadRunning = TRUE;
		return cmdThreadRunning;
	}
	return FALSE;
}
CMD_CAPI(BOOL) MStopRunCmdThread()
{
	if (cmdThreadRunning)
	{
		cmdThreadCanRun = FALSE;
		if (hCmdThread)
		{
			DWORD dw = WaitForSingleObject(hCmdThread, 100);
			if (dw == WAIT_TIMEOUT) {
				if (NT_SUCCESS(MTerminateThreadNt(hCmdThread)))
					LogInfo(L"RunCmdThread Terminated.");
				else LogWarn(L"RunCmdThread Terminate failed!");
			}
			if (hCmdThread) { CloseHandle(hCmdThread); hCmdThread = 0; }
			cmdThreadRunning = FALSE;
			return 1;
		}
		cmdThreadRunning = FALSE;
	}
	return FALSE;
}




