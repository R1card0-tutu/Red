# Social Engineering

***

## Type of Social Engineering

* Phishing
  * Spear phising
  * Whaling
* Vishing and Smishing
* Pretexting
* Baiting
* Tailgating and Piggybacking
* Quid Pro Quo

## Email as primary Transportation

`SPF` is a record that is part of your domain's DNS that contains a list of all the IP addresses that are permitted to send email on behalf of your domain

```bash
dig +short txt microdoft.com
```

`DKIM` allows the receiver to check that an email claimed to have come from a specific domain was indeed authorized by the owner of that domain

```bash
dig dkim._domainkey.redhat.com
```

`DMARC` is an email authentication protocol. It is designed to give email domain owners the ability to protect their domain from unauthorized use, commonly known as email spoofing

```bash
dig +short TXT _dmarc.redhat.com
```

`SPoofcheck` A program that checks if a domain can be spoofed from. The program checks SPF and DMARC records for weak configurations that allow spoofing.

<https://github.com/BishopFox/spoofcheck>

```bash
./spoofcheck.py redhat.com
```

### Email Reconnaissance

* <https://app.snov.io/domain-search?name=irancell.ir>
* <https://rocketreach.co>
* <https://Hinuter.io>

### Fake Email

* <https://www.guerrillamail.com/inbox>
* <http://www.anonymailer.net>
* <https://www.spoofbox.com/en/app/spoof-email>

### Enumerate users by Email

* https://canarytokens.org/

## Phishing Framework

### Gophish

`gophish` is a powerful, open-source phishing framework that makes it easy to test
your organization's exposure to phishing

1. access panel

2. https://127.0.0.1:3333/

3. create email template

4. create landing page 

5. create users & Group

6. create sending profile

7. create campaigns
