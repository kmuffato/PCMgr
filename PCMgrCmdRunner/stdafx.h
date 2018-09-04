// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

#ifdef PCMGRCMDRUNNER_EXPORTS
#define CMD_API __declspec(dllexport)
#define CMD_CAPI(x) extern "C" CMD_API x
#else
#define CMD_API __declspec(dllimport)
#define CMD_CAPI(x) extern "C" CMD_API x
#endif

// TODO: 在此处引用程序需要的其他头文件
