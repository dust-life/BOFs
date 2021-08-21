#include <windows.h>
#include <tchar.h>
#include "beacon.h" 


WINADVAPI BOOL WINAPI ADVAPI32$OpenProcessToken(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);
WINBASEAPI HANDLE WINAPI KERNEL32$GetCurrentProcess(VOID);
WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(VOID);
WINADVAPI BOOL WINAPI ADVAPI32$AdjustTokenPrivileges(HANDLE TokenHandle,BOOL DisableAllPrivileges,PTOKEN_PRIVILEGES NewState,DWORD BufferLength,PTOKEN_PRIVILEGES PreviousState,PDWORD ReturnLength);
WINADVAPI BOOL WINAPI ADVAPI32$LookupPrivilegeValueA(LPCWSTR lpSystemName,LPCWSTR lpName,PLUID lpLuid);
WINBASEAPI BOOL WINAPI KERNEL32$CloseHandle(HANDLE hObject);

void go(char* args, int length) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;
    datap  parser;
    char* privilege;

    BeaconDataParse(&parser, args, length);
    privilege = BeaconDataExtract(&parser, NULL);
    BeaconPrintf(CALLBACK_OUTPUT, "Enable %s", privilege);
    if (!ADVAPI32$OpenProcessToken(KERNEL32$GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
    {
	BeaconPrintf(CALLBACK_ERROR, "OpenProcessToken error");
	return FALSE;
    }
    else
    {
        BeaconPrintf(CALLBACK_OUTPUT, "OpenProcessToken Success");
    }

    if (!ADVAPI32$LookupPrivilegeValueA(
        NULL,            // lookup privilege on local system
        privilege,   // privilege to lookup 
        &luid))        // receives LUID of privilege
    {
        BeaconPrintf(CALLBACK_ERROR, "LookupPrivilegeValue error: %u\n", KERNEL32$GetLastError());
        KERNEL32$CloseHandle(hToken);
        return FALSE;
    }
    else
    {
        BeaconPrintf(CALLBACK_OUTPUT, "LookupPrivilegeValue Success");
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Enable the privilege or disable all privileges.

    if (!ADVAPI32$AdjustTokenPrivileges(
        hToken,
        FALSE,
        &tp,
        sizeof(TOKEN_PRIVILEGES),
        (PTOKEN_PRIVILEGES)NULL,
        (PDWORD)NULL))
    {
        BeaconPrintf(CALLBACK_ERROR, "AdjustTokenPrivileges error: %u\n", KERNEL32$GetLastError());
        KERNEL32$CloseHandle(hToken);
        return FALSE;
    }
    else
    {
        BeaconPrintf(CALLBACK_OUTPUT, "AdjustTokenPrivileges Success");
    }

    if (KERNEL32$GetLastError() == ERROR_NOT_ALL_ASSIGNED)

    {
        BeaconPrintf(CALLBACK_ERROR, "The token does not have the specified privilege. \n");
        KERNEL32$CloseHandle(hToken);
        return FALSE;
    }
    else
    {
        BeaconPrintf(CALLBACK_OUTPUT, "Enable %s Success", privilege);
        KERNEL32$CloseHandle(hToken);
        
    }
}
