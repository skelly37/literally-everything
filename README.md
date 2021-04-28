# My Linux scripts & configs

## [Update checker for the StevenBlack's unified + gambling + porn hosts file (Python3)](https://github.com/skelly37/my-linux/blob/main/checkhosts/checkhosts.py)/[polish](https://github.com/skelly37/my-linux/blob/main/checkhosts/checkhosts-PL.py)

This Python3 script checks whether there was an update of the StevenBlack's unified + gambling + porn hosts file.
If there was, the user may agree to replace the older file from /etc/hosts with the newest one

### Prerequisites
* `$ chmod u+x checkhosts`

To use different set, just copy the link from the StevenBlack's repo and assign it to the LINK in the source code.

Premade binaries make use of the unified + gambling + porn hosts file.

Read carefully hosts_whitelist.txt! Whitelist support added.

### How to use whitelist?
* Enter either full lines from /etc/hosts like '0.0.0.0 www-google-analytics.l.google.com' or just keywords like 'google' to whitelist all of the Google domains.
* Paste the links the same way there are in the /etc/hosts — no tabulating, no spacing, no commas etc.
* Enter your own whitelist this way or delete the file after reading.

**[StevenBlack's hosts repo](https://github.com/StevenBlack/hosts)**

## [Update pacman packages, AUR software and summon checkhosts (Bash)](https://github.com/skelly37/my-linux/blob/main/update)

Update everything on the PC with just one *update* command!

