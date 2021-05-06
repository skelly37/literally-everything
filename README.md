# My Linux scripts & configs

## Update checker for the StevenBlack's unified + gambling + porn hosts file ([bash](https://github.com/skelly37/literally-everything/blob/main/checkhosts/checkhosts) + Python3 [en](https://github.com/skelly37/literally-everything/blob/main/checkhosts/checkhosts.py)/[pl](https://github.com/skelly37/literally-everything/blob/main/checkhosts/checkhosts-pl.py))

This Python3 script checks whether there was an update of the StevenBlack's unified + gambling + porn hosts file.
If there was, the user may agree to replace the older file from /etc/hosts with the newest one

### Prerequisites
* **wget** 
* `$ chmod a+x checkhosts && chmod a+x checkhosts-py && chmod a+x update`

To use different set, just copy the link from the StevenBlack's repo and assign it to the LINK in the bash script `checkhosts`.

Premade Python binary was compiled for Artix Linux but the source code does not depent on the OS.

Whitelist support

### How to use whitelist?
* Paste links/domains into WHITELIST in `checkhosts` script. Correct formatting: WHITELIST = ("domain1" "domain2" "domain3") *you can use ' instead of ", though*
* Enter either full lines from /etc/hosts like '0.0.0.0 www-google-analytics.l.google.com' or just keywords like 'google' to whitelist all of the Google domains.
* Paste the links the same way there are in the /etc/hosts — no tabulating, no spacing, no commas etc.

**[StevenBlack's hosts repo](https://github.com/StevenBlack/hosts)**

## [Update pacman packages, AUR software and summon checkhosts (Bash)](https://github.com/skelly37/literally-everything/blob/main/update)

Update everything on the PC with just one *update* command!

# Functions
## [Python3](https://github.com/skelly37/literally-everything/blob/main/functions/python3/)
### [Displaying a progressbar in terminal](https://github.com/skelly37/literally-everything/blob/main/functions/python3/my_progressbar.py)

Display script's progress in a pacman-like prograssbar with a loop. Usage documented in the source code.

Example:

```
from time import sleep
from my_progressbar import show_progressbar
	      
        max = 153
        show_progressbar(0, max)
        
        for count in range(max):
            sleep(0.05) 
            #some code
            show_progressbar(count+1, max)
  ```



# Things not to forget
## Configuring USB printer Brother MFC 7860DW on Artix Linux with runit
### Prerequisites
* `$ paru -S brother-mfc-7860dw brscan4`

Replace *paru* with your preferred AUR helper prefix or simply build the AUR packages manually

* `# pacman -S cups-runit simple-scan`

The latter may be any other scanning software

* `# cp /etc/runit/sv/cupsd /run/runit/service/`
* `# sv up cupsd && sv status cupsd`

### Setting up the printer
* `# lpadmin -p BROTHER-MFC-7860DW -E -v [PORT-USB] -m MFC7860DW.ppd`

example:

* `# lpadmin -p BROTHER-MFC-7860DW -E -v "usb://Brother/MFC-7860DW?serial=E6343844N360681"-m MFC7860DW.ppd`

### Setting up the scanner
* `# brsaneconfig4 -a name=Brother_MFC-7860DW model=MFC-7860DW ip=192.000.000.192`

Only the IP modification is required. You have to set up a static IP for your printer. Either via your router or via the settings of the printer.

### Resources
* https://wiki.archlinux.org/index.php/CUPS#CLI_tools
* https://juancjuarez.wordpress.com/2014/02/17/archlinux-brother-mfc-7860dw/
* https://forum.artixlinux.org/index.php/topic,767.0.html

