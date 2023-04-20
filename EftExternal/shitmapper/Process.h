//#pragma once
//
//#include <windows.h>
//#include <tlhelp32.h>
//#include <psapi.h>  
//#include <stdio.h>
//
//bool isModule(DWORD processID, const char* module, bool debug = false) {
//    {
//        HMODULE hMods[1024];
//        HANDLE hProcess;
//        DWORD cbNeeded;
//        unsigned int i;
//
//        // Print the process identifier.
//
//        printf("\nProcess ID: %u\n", processID);
//
//        // Get a handle to the process.
//
//        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
//            PROCESS_VM_READ,
//            FALSE, processID);
//        if (NULL == hProcess)
//            return NULL;
//
//        // Get a list of all the modules in this process.
//
//        if (K32EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
//        {
//            for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
//            {
//                TCHAR szModName[MAX_PATH];
//
//                // Get the full path to the module's file.
//
//                if (K32GetModuleFileNameExA(hProcess, hMods[i], szModName,
//                    sizeof(szModName) / sizeof(TCHAR)))
//                {
//                    // Print the module name and handle value.
//                    if (strstr(szModName, module)) {
//                        if (debug)
//                            printf(TEXT("\t%s (0x%08X)\n"), szModName, hMods[i]);
//                        CloseHandle(hProcess);
//                        return true;
//                    }
//                }
//            }
//        }
//
//        // Release the handle to the process.
//
//        CloseHandle(hProcess);
//        return 0;
//    }
//}
//
//HMODULE GetModuleAddres(DWORD processID, const char* module, bool debug = false)
//{
//    HMODULE hMods[1024];
//    HANDLE hProcess;
//    DWORD cbNeeded;
//    unsigned int i;
//
//    // Print the process identifier.
//    if (debug)
//        printf("\nProcess ID: %u\n", processID);
//
//    // Get a handle to the process.
//
//    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
//        PROCESS_VM_READ,
//        FALSE, processID);
//    if (NULL == hProcess)
//        return NULL;
//
//    // Get a list of all the modules in this process.
//
//    if (K32EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
//    {
//        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
//        {
//            TCHAR szModName[MAX_PATH];
//
//            // Get the full path to the module's file.
//
//            if (K32GetModuleFileNameExA(hProcess, hMods[i], szModName,
//                sizeof(szModName) / sizeof(TCHAR)))
//            {
//                // Print the module name and handle value.
//                if (strstr(szModName, module)) {
//                    if (debug)
//                        printf(TEXT("\t%s (0x%08X)\n"), szModName, hMods[i]);
//                    CloseHandle(hProcess);
//                    return hMods[i];
//                }
//            }
//        }
//    }
//
//    // Release the handle to the process.
//
//    CloseHandle(hProcess);
//    return 0;
//}
//
//int GetProcessIdByName(const char* processname, bool debug = false)
//{
//    HANDLE hProcessSnap;
//    PROCESSENTRY32 pe32;
//    DWORD result = NULL;
//
//    // Take a snapshot of all processes in the system.
//    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//    if (INVALID_HANDLE_VALUE == hProcessSnap) return(FALSE);
//
//    pe32.dwSize = sizeof(PROCESSENTRY32); // <----- IMPORTANT
//
//    // Retrieve information about the first process,
//    // and exit if unsuccessful
//    if (!Process32First(hProcessSnap, &pe32))
//    {
//        CloseHandle(hProcessSnap);          // clean the snapshot object
//        if (debug)
//            printf("Failed to gather information on system processes! \n");
//        return(NULL);
//    }
//
//    do
//    {
//        if (0 == strcmp(processname, pe32.szExeFile))
//        {
//            result = pe32.th32ProcessID;
//            break;
//        }
//    } while (Process32Next(hProcessSnap, &pe32));
//
//    CloseHandle(hProcessSnap);
//
//    return result;
//}