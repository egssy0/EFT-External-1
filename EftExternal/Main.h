#pragma once
#include <windows.h>
#include <winternl.h>
#include <fstream>
#include <string>
#include <vector>
#include <tlhelp32.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "ntdll.lib")


EXTERN_C
{
    NTSTATUS NTAPI NtQuerySystemInformation(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID SystemInformation,
    IN ULONG SystemInformationLength,
    OUT PULONG ReturnLength OPTIONAL
    );
}



